#include "uoswalletmanager.h"
#include "uoswallet.h"

#include "codebase/ec/uos_key_encode.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>

UOSWalletManager::UOSWalletManager()
{
    defaultExists = false;
    dir = QCoreApplication::applicationDirPath() + "/data";
    if (!QFileInfo(dir).exists()) {
        QDir curDir;
        bool ret = curDir.mkpath(dir);
        Q_ASSERT(ret);
    }

    loadPasswords();
}

UOSWalletManager &UOSWalletManager::instance()
{
    static UOSWalletManager manager;
    return manager;
}

QString UOSWalletManager::create(const QString &name)
{
    QString password = genPassword();
    if (dir.at(dir.length() - 1) != '/' ||
            dir.at(dir.length() - 1) != '\\')
        dir += '/';
    QFileInfo fileInfo(dir + name + UOS_WALLET_FILE_EXT);
    if (fileInfo.exists()) {
        QMessageBox::critical(NULL, "Error", "Wallet " + name + " already exists!");
        return QString();
    }

    UOSWallet wallet;
    wallet.setPassword(password);
    wallet.unlock(password);
    wallet.saveFile(fileInfo.absoluteFilePath());
    wallet.lock();
    wallet.unlock(password);

    wallets.insert(name, wallet);

    return password;
}

void UOSWalletManager::open(const QString &name)
{
    QFileInfo info(QDir(dir), name);
    UOSWallet wallet;
    if (!wallet.loadFile(info.absoluteFilePath())) {
        return;
    }

    auto nameWithoutExt = name;
    auto strEnd         = name.right(UOS_WALLET_FILE_EXT.length());
    if (strEnd.compare(UOS_WALLET_FILE_EXT, Qt::CaseInsensitive) == 0) {
        nameWithoutExt = name.left(name.length() - UOS_WALLET_FILE_EXT.length());
    }

    wallets.insert(nameWithoutExt, wallet);
    checkDefaultWallet(nameWithoutExt);
}

void UOSWalletManager::openAll()
{
    QDir walletDir(dir);
    QStringList filters;
    filters << ("*" + UOS_WALLET_FILE_EXT);
    auto files = walletDir.entryList(filters, QDir::Files);
    if (files.size()) {
        for (const auto& f : files) {
            open(f);
        }
    }
}

bool UOSWalletManager::isLocked(const QString &name)
{
    if (wallets.find(name) == wallets.end()) {
        // wallet not found!
        return false;
    }

    return wallets[name].isLocked();
}

void UOSWalletManager::lockAll()
{
    //return;
    for (auto& item : wallets) {
        if (!item.isLocked()) {
            item.lock();
        }
    }
}

void UOSWalletManager::lock(const QString &name)
{
    if (wallets.find(name) == wallets.end()) {
        // wallet not found, should never be here!
        return;
    }
    //return;
    auto& wallet = wallets[name];
    if (!wallet.isLocked()) {
        wallet.lock();
    }
}

void UOSWalletManager::unlock(const QString &name, const QString &password)
{
    if (wallets.find(name) == wallets.end()) {
        // wallet not found, should never be here!        
        return;
    }

    auto& wallet = wallets[name];
    if (wallet.isLocked()) {
        wallet.unlock(password);
    }
}

void UOSWalletManager::importKey(const QString &name, const QString &wif)
{
    if (wallets.find(name) == wallets.end()) {
        return;
    }

    auto& wallet = wallets[name];
    if (wallet.isLocked()) {
        // wallet is locked, nothing we can do.
        return;
    }

    if (!wallet.importKey(wif)) {
        QMessageBox::warning(nullptr, "Error", "Import key failed!");
    }
}

void UOSWalletManager::newKey( const QString &name)
{
    if (wallets.find(name) == wallets.end()) {
        return;
    }

    auto& wallet = wallets[name];
    if (wallet.isLocked()) {
        // wallet is locked, nothing we can do.
        return;
    }

    if (!wallet.newKey()) {
        QMessageBox::warning(nullptr, "Error", "new key failed!");
    }
}

QMap<QString, UOSWallet> UOSWalletManager::listKeys(wallet_state state)
{
    QMap<QString, UOSWallet> result;
    for (auto itr = wallets.cbegin();
         itr != wallets.cend(); ++itr) {
        if (state == ws_all || state == itr.value().isLocked()) {
            result.insert(itr.key(), itr.value());
        }
    }

    return result;
}

QVector<QPair<QString, bool> > UOSWalletManager::listWallets(wallet_state state)
{
    QVector<QPair<QString, bool>> result;
    if (wallets.size() == 0) {
        return result;
    }

    for (auto itr = wallets.cbegin();
         itr != wallets.cend(); ++itr) {
        if (state == ws_all || state == itr.value().isLocked()) {
            result.push_back(QPair<QString, bool>(itr.key(), itr.value().isLocked()));
        }
    }

    return result;
}

void UOSWalletManager::loadPasswords()
{
    QFile file(passwordsFile());
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    auto doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) {
        return;
    }

    auto array = doc.array();
    for (int i = 0; i < array.size(); ++i) {
        auto obj = array.at(i).toObject();
        if (obj.isEmpty()) {
            continue;
        }

        auto key = obj.keys().at(0);
        passwords.insert(key, obj.value(key).toString());
    }
}

void UOSWalletManager::addPasswords(const QString &walletName, const QString &passwd)
{
    if (wallets.find(walletName) == wallets.end()) {
        QMessageBox::warning(nullptr, "Error", "No such wallet.");
        return;
    }

    if (passwords.find(walletName) == passwords.end()) {
        passwords.insert(walletName, passwd);
    } else {
        passwords[walletName] = passwd;
    }

    savePasswords();
}

QString UOSWalletManager::getPassword(const QString &walletName)
{
    QString passwd;
    if (passwords.find(walletName) != passwords.end()) {
        passwd = passwords.value(walletName);
    }

    return passwd;
}

void UOSWalletManager::savePasswords()
{
    QFile file(passwordsFile());
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonArray array;
    for (auto itr = passwords.constBegin();
         itr != passwords.constEnd(); ++itr) {
        QJsonObject obj;
        obj.insert(itr.key(), QJsonValue(itr.value()));
        array.append(QJsonValue(obj));
    }

    file.write(QJsonDocument(array).toJson());
}

void UOSWalletManager::signTransaction(SignedTransaction &txn, const std::vector<std::string> &pubKeys, const TypeChainId &cid)
{
    if (pubKeys.empty()) {
        return;
    }

    for (const auto& k : pubKeys) {
        bool found = false;

        for (auto itr = wallets.constBegin();
             itr != wallets.constEnd(); ++itr) {
            if (itr.value().isLocked()) {
                continue;
            }

            auto wif = itr.value().getPrivateKey(QString::fromStdString(k)).toStdString();
            if (wif.empty()) {
                continue;
            }

            auto priKey = uos_key::get_private_key_by_wif(wif);
            txn.sign(priKey, cid);

            found = true;
            break;
        }

        if (found) {
            break;
        }
    }
}

QString UOSWalletManager::genPassword()
{
    uos_key key;
    return UOS_WALLET_PASSWD_PREFIX + QString::fromStdString(key.get_wif_private_key());
}

QString UOSWalletManager::passwordsFile()
{
    auto passwdFile = dir;
    if (passwdFile.at(passwdFile.length() - 1) != '/' ||
            passwdFile.at(passwdFile.length() - 1) != '\\')
        passwdFile += '/';
    passwdFile += "password";
    return passwdFile;
}

void UOSWalletManager::checkDefaultWallet(const QString &fileWithoutExt)
{
    if (!defaultExists && fileWithoutExt == UOS_WALLET_DEFAULT_NAME) {
        defaultExists = true;
    }
}
