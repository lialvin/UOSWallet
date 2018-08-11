#ifndef UOSWALLETMANAGER_H
#define UOSWALLETMANAGER_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QPair>

#include "uoswallet.h"

#include "codebase/chain/signedtransaction.h"

class UOSWalletManager
{
public:
    enum wallet_state
    {
        ws_all = -1,
        ws_unlocked = 0,
        ws_locked = 1
    };

public:
    static UOSWalletManager& instance();

    QString create(const QString& name);
    void open(const QString& name);
    void openAll();

    bool defaultWalletExists() { return defaultExists; }
    QString defaultWalletName() { return UOS_WALLET_DEFAULT_NAME; }

    bool isLocked(const QString& name);
    void lockAll();
    void lock(const QString& name);
    void unlock(const QString& name, const QString& password);

    void importKey(const QString& name, const QString& wif);

    QMap<QString, UOSWallet> listKeys(wallet_state state);
    QVector<QPair<QString, bool>> listWallets(wallet_state state);

    void addPasswords(const QString& walletName, const QString& passwd);
    QString getPassword(const QString& walletName);
    void savePasswords();

    void signTransaction(SignedTransaction& txn, const std::vector<std::string>& pubKeys, const TypeChainId& cid);

private:
    UOSWalletManager();

    QString genPassword();
    QString passwordsFile();
    void checkDefaultWallet(const QString& fileWithoutExt);
    void loadPasswords();

private:
    const QString UOS_WALLET_PASSWD_PREFIX  = "PW";
    const QString UOS_WALLET_FILE_EXT       = ".wallet";
    const QString UOS_WALLET_DEFAULT_NAME   = "default";  
    
    QMap<QString, UOSWallet>    wallets;
    QMap<QString, QString>      passwords;
    
    QString dir;
    bool    defaultExists;
};

#endif // UOSWALLETMANAGER_H
