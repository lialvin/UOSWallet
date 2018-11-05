# About/关于

**UosDevTool** is a cross-platform UOS PC wallet tool,which is developed by alvin.

  
-------------------------------

# Menu/目录
+ [Overview  简介](#1)
+ [ENVIRONMENT  开发和使用环境](#2)

------------------------------

<h2 id="1">Overview/简介</h2>

&emsp;&emsp;The UosDevTool program is a light weighted wallet build on UOSIO ecology. It provides private basic key store with encryptions, signature, validation functions, and etc. Developers can use this tool connect the UOSIO testnet, and test the wallet/account/contracts interface in a more convenient way.

&emsp;&emsp;UosDevTool是一个建立在UOSIO生态上的钱包工具。它提供了基础的钱包功能，包含了私钥加密管理、签名校验模块。开发者可以使用UOS开发助手连接UOSIO网络，更便捷地对钱包、账号、合约接口等进行开发和测试。


------------------------------
<h2 id="2">ENVIRONMENT/开发和使用环境</h2>

**Compile from source code/如何从源码编译：**

&emsp;MACOS、WINDOWS、UBUNTU

&emsp;1. install [QT](https://www.qt.io/download) >= 5.8

&emsp;2. download our git repository.
>`git clone --recurse-submodules https://github.com/lialvin/UosDevTool.git`

&emsp;3. open Qt Creator and choose "Open Project", select the "src/UosDevTool.pro" and open

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


