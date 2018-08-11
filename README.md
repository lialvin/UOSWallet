# About/关于

**UOSWallet** is a cross-platform UOS PC wallet tool,which is developed by alvin.

  
-------------------------------

# Menu/目录
+ [Overview  简介](#1)
+ [ENVIRONMENT  开发和使用环境](#2)
+ [Wallet Functions  钱包功能](#3)
+ [Account Functions  账号功能](#4)
+ [Contract Functions  合约功能](#5)
+ [Transaction Checker  交易核查](#6)
+ [About lialvin  有关欧链](#7)
+ [LICENSE  版权](#8)

------------------------------

<h2 id="1">Overview/简介</h2>

&emsp;&emsp;The UOSWallet program is a light weighted wallet build on UOSIO ecology. It provides private basic key store with encryptions, signature, validation functions, and etc. Developers can use this tool connect the UOSIO testnet, and test the wallet/account/contracts interface in a more convenient way.

&emsp;&emsp;UOSWallet是一个建立在UOSIO生态上的钱包工具。它提供了基础的钱包功能，包含了私钥加密管理、签名校验模块。开发者可以使用UOS开发助手连接UOSIO网络，更便捷地对钱包、账号、合约接口等进行开发和测试。


------------------------------
<h2 id="2">ENVIRONMENT/开发和使用环境</h2>

**Compile from source code/如何从源码编译：**

&emsp;MACOS、WINDOWS、UBUNTU

&emsp;1. install [QT](https://www.qt.io/download) >= 5.8

&emsp;2. download our git repository.
>`git clone --recurse-submodules https://github.com/lialvin/UOSWallet.git`

&emsp;3. open Qt Creator and choose "Open Project", select the "src/UOSWallet.pro" and open

&emsp;4. select Build from QT menu and Run it.


> For ubuntu, if build with errors like `connot find -lGL`, this means the openGL development library is missing.
Just using this command to install:
`sudo apt-get install build-essential libgl1-mesa-dev`



> For Ubuntu: Tested on Ubuntu 16.04 x64, you should `chmod +x start.sh`, then use `./start.sh` . 


**DEPENDENCYS/依赖库:**

&emsp;1.our ECDSA is based on micro-ecc

&emsp;&emsp;椭圆曲线算法实现来自micro-ecc

&emsp;&emsp;https://github.com/kmackay/micro-ecc

&emsp;2.We build a Publicly Verifiable Secret Sharing on secp256k1 which is published by Schoenmakers on crypto99 conference.

&emsp;&emsp;我们在椭圆曲线secp256k1上实现了Schoenmakers在crypto99上提出的Publicly Verifiable Secret Sharing

&emsp;&emsp;https://github.com/songgeng87/PubliclyVerifiableSecretSharing


------------------------------

<h2 id="3">Wallet Functions/钱包功能</h2>

### Settings/设置
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/setting.PNG)

### Create a wallet/创建钱包
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/wallet.PNG)

### Create & import a private key/创建和导入私钥
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/ImportKey.PNG)

### Lock or Unlock a wallet/锁定和解锁钱包
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/UnlockWallet.PNG)


<h2 id="4">Account Functions/账号功能</h2>

### Create account/创建账号
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/account.PNG)

### Get Account Status/账号状态
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/GetAccount.PNG)

### Get Account History/账号交易历史
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/GetTransaction.PNG)

### Get Account Servants/账号子集
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/GetServants.PNG)



<h2 id="5">Contract Functions/合约功能</h2>

### Send a transaction/发起合约调用
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/Push.PNG)

### Get data table of a contract/查看合约数据表
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/GetTable.PNG)


<h2 id="6">Transaction Checker/交易核查</h2>

### 根据交易原文和签名，验证链上某交易是否成立/Using the action message with its signature,we can check if a transaction is signed by the owener of a given public key. 
![](https://github.com/lialvin/UOSWallet/raw/master/screenshots/Checker.PNG)



