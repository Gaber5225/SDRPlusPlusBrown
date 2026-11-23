# DE BG9JXB，
### 我跟workbuddy苦苦求了三天，AI菩萨终于给我赐下了汉化版的SDR++brown，顺带修复了原版的一点bug，欢迎各位使用，73！
# SDR++Brown（分叉版），并非原版那个"无臃肿"的 SDR 软件

[更新日志](changelog.md)

**请不要将本分叉版的 bug 报告给原作者。请使用原版应用，它更好用。**

**本分叉版的 bug 请在本页的 ISSUES 中报告。**

如需了解基本功能列表，请参阅[上游项目页面](https://github.com/AlexandreRouma/SDRPlusPlus)。

已合并至上游版本：`bad387c0`（2026-11-18）。最后一次完整同步点为 `65a0e11d`（2025-12-12）；比该同步点更新的上游提交是逐条手动移植的。

分叉版功能列表请参阅 [brown fork 页面](https://sdrpp-brown.san.systems)。

Windows 安装故障排查：https://youtu.be/Q3CV5U-2IIU

## 致谢 / 鸣谢

谨向以下人员致以感谢与敬意：

* 原作者 Alexandre Rouma，感谢他出色的[工作](https://github.com/AlexandreRouma/SDRPlusPlus)。同时感谢上游项目的所有贡献者。
* MSHV 作者 LZ2HV，感谢他出色的[工作](http://lz2hv.org/mshv)。
* logmmse/python 的作者们，感谢他们出色的[工作](https://github.com/wilsonchingg/logmmse)。
* OMLSA 的作者们，感谢他们出色的[思路](https://github.com/yuzhouhe2000/OMLSA-IMCRA)与[实现](https://github.com/xiaochunxin/OMLSA-MCRA)。
* imgui-notify 作者，感谢他出色的[工作](https://github.com/patrickcjk/imgui-notify)
* implot 作者，感谢他出色的[工作](https://github.com/epezent/implot/)
* alexander-sholohov（github），感谢他对 soapy_sdr 模块的工作。
* Cropinghigh / Indir，感谢他在额外 VHF 模式上的[工作](github.com/cropinghigh/sdrpp-vhfvoiceradio)。
* monolifed，感谢他的 [pbkdf2 纯头文件实现](https://github.com/monolifed/pbkdf2-hmac-sha256)
* Kristijonas Adomaitis 与 OnAir 贡献者们，感谢他们带来的 rx888 以及未来可能并入此处的 OnAir 部分。
* Davide Belloli（[dbdexter-dev](https://github.com/dbdexter-dev)），感谢他的 [sdrpp_radiosonde](https://github.com/dbdexter-dev/sdrpp_radiosonde) 模块和 [sondedump](https://github.com/dbdexter-dev/sondedump) 库。
* ruse39，感谢他在代码质量上的贡献。
* "prog"（X 上的 [@prog](https://x.com/prog)，Youssef Touil，Airspy 作者），感谢他提供了 dabplus_decoder 模块所遵循的 DAB+ 源码，以及构建该源码所用的 SDR# VDK（Vibe Development Kit）。
* William Yang（[williamyang98](https://github.com/williamyang98)），感谢他的 [DAB-Radio](https://github.com/williamyang98/DAB-Radio) 和 [ViterbiDecoderCpp](https://github.com/williamyang98/ViterbiDecoderCpp)；感谢 Phil Karn（KA9Q）的 Reed-Solomon 与 Viterbi 算法、Tristan Brindle 的 `span` 实现，以及 fmt、faad2 和 mpg123 的作者们，为 dabplus_decoder 内部的解码器所做的工作。

## 反馈

发现问题了？这个分叉版比原版更差？请提交一个 [issue](https://github.com/sannysanoff/SDRPlusPlusBrown/issues)。

## 调试提示

* 在 Windows 的 VirtualBox 环境中调试时，请从 https://downloads.fdossena.com/Projects/Mesa3D/Builds/MesaForWindows-x64-20.1.8.7z 下载 mesa 的 opengl32.dll。
* 请务必把 rtaudiod.dll 放到构建目录的根目录下，否则音频输出（sink）无法加载。
* 用系统监视器来排查那些加载失败的缺失 dll。

## 本地 Android 构建：

* 在 ~/.gradle/gradle.properties 中加入这一行：sdrKitRoot=/home/user/SDRPlusPlus/android-sdr-kit/sdr-kit
  * 可以从以下地址获取并构建：https://github.com/AlexandreRouma/android-sdr-kit
  * docker build --platform linux/amd64 -t android-sdr-kit  .
  * docker start android-sdr-kit    # 它会退出
  * docker cp be03210da56a:/sdr-kit .    # 会创建一个包含已构建二进制库的目录，请将 be03210da56a 替换为 'docker ps -a' 得到的 id
* 在 Android Studio 中使用 jdk11 来运行 gradle。Android Studio -> Settings -> ... -> Gradle -> Gradle JDK 。当你遇到各种 java.io 不可访问字段错误时需要这样做。
* 万一遇到无效 keystore 错误（使用 jdk11 时不应发生）：
  * 你可以用当前 jdk 版本创建一个新 keystore：
    ~/soft/jdk8/bin/keytool -genkey -v -keystore debug2.keystore -storepass android -alias androiddebugkey -keypass android -keyalg RSA -keysize 2048 -validity 10000
  * 在 app/build.gradle 中使用这个文件名（debug2.keystore），并在 signingConfigs -> debug 段中填入相应密码。

祝你好运。

---

## 以下为原文（Original README）

# SDR++Brown (fork), is not the original bloat-free SDR software


[Changelog](changelog.md)

**Please do not report bugs in this fork to original author. Use original application, it works better.**

**Report bugs in this fork on this page, in ISSUES.** 

Please see [upstream project page](https://github.com/AlexandreRouma/SDRPlusPlus) for the basic list of its features.

Merged up to: upstream `bad387c0` (2026-11-18). The last full sync point is `65a0e11d` (2025-12-12); upstream commits newer than that are ported by hand, one at a time.

Please see [brown fork page](https://sdrpp-brown.san.systems) for list of fork features.

WINDOWS INSTALL TROUBLESHOOTING: https://youtu.be/Q3CV5U-2IIU

## Thanks / Credits

Thanks and due respect to:
 
* original author, Alexandre Rouma, for his great [work](https://github.com/AlexandreRouma/SDRPlusPlus). Due credits go to all contributors in the upstream project. 
* MSHV author, LZ2HV, for his great [work](http://lz2hv.org/mshv).
* logmmse/python authors for their great [work](https://github.com/wilsonchingg/logmmse).
* OMLSA authors for their great [idea](https://github.com/yuzhouhe2000/OMLSA-IMCRA) and [implementation](https://github.com/xiaochunxin/OMLSA-MCRA).
* imgui-notify author for his great [work](https://github.com/patrickcjk/imgui-notify)
* implot author for his great [work](https://github.com/epezent/implot/)
* alexander-sholohov (github) for his work on soapy_sdr module.
* Cropinghigh / Indir for his [work](github.com/cropinghigh/sdrpp-vhfvoiceradio) on extra VHF modes.
* monolifed for his [pbkdf2 header-only implementation](https://github.com/monolifed/pbkdf2-hmac-sha256)  
* Kristijonas Adomaitis and OnAir contributors, for the rx888 and future OnAir parts that may end up here
* Davide Belloli ([dbdexter-dev](https://github.com/dbdexter-dev)) for his [sdrpp_radiosonde](https://github.com/dbdexter-dev/sdrpp_radiosonde) module and [sondedump](https://github.com/dbdexter-dev/sondedump) library
* ruse39 for his contributions on code quality
* "prog" ([@prog](https://x.com/prog) on X, Youssef Touil, the Airspy author) for the DAB+ source the dabplus_decoder module follows, and for the SDR# VDK (Vibe Development Kit) that source is built with.
* William Yang ([williamyang98](https://github.com/williamyang98)) for [DAB-Radio](https://github.com/williamyang98/DAB-Radio) and [ViterbiDecoderCpp](https://github.com/williamyang98/ViterbiDecoderCpp), Phil Karn (KA9Q) for the Reed-Solomon and Viterbi algorithms, Tristan Brindle for the `span` implementation, and the authors of fmt, faad2 and mpg123, for the decoders inside dabplus_decoder.

## Feedback

Found an issue? Fork is worse than original? File an [issue](https://github.com/sannysanoff/SDRPlusPlusBrown/issues).

## Debugging reminders

* to debug in windows in virtualbox env, download mesa opengl32.dll from https://downloads.fdossena.com/Projects/Mesa3D/Builds/MesaForWindows-x64-20.1.8.7z
* make sure you put rtaudiod.dll in the build folder's root otherwise audio sink will not load.
* use system monitor to debug missing dlls while they fail to load.

## Local Android build:

* put into your ~/.gradle/gradle.properties this line: sdrKitRoot=/home/user/SDRPlusPlus/android-sdr-kit/sdr-kit
  * it can obtained + built from: https://github.com/AlexandreRouma/android-sdr-kit 
  * docker build --platform linux/amd64 -t android-sdr-kit  .
  * docker start android-sdr-kit    # it will exit
  * docker cp be03210da56a:/sdr-kit .    # will create directory with built binary libs, replace be03210da56a with id obtained from 'docker ps -a'
* use jdk11 for gradle in android studio. Android Studio -> Settings -> ... -> Gradle -> Gradle JDK . This is needed if you have various errors with java.io unaccessible fields.
* in case of invalid keystore error (should not happen with jdk11): 
  * you may create new keystore with current jdk version:
    ~/soft/jdk8/bin/keytool -genkey -v -keystore debug2.keystore -storepass android -alias androiddebugkey -keypass android -keyalg RSA -keysize 2048 -validity 10000
  * use this filename (debug2.keystore) in app/build.gradle along with passwords in the signingConfigs -> debug section.

Good luck.
