# Qt Lab 2

这是一个使用Qt框架开发的祖玛游戏。

## 编译和运行说明

课程相关视频，请及时在完成作业之前观看：

- [Qt安装教程](https://meeting.tencent.com/crm/NXBPkX8K4c)
- [课前准备教程](https://meeting.tencent.com/crm/lR9GLWENe4)

### 前提条件

- Git
- Qt 6.0或更高版本
- C++11兼容的编译器
- IDE: Cursor / VSCode （课堂上我们以 Cursor 来演示，其他的 IDE 也可以，包括但不限于 VS 等）

### Qt入门

在 Windows 中，可以从[官网](https://www.qt.io/download-qt-installer-oss)下载qt，请参考[Qt安装教程](https://meeting.tencent.com/crm/NXBPkX8K4c)。

如果安装过程中出现网络错误，可以尝试重新下载或更换上网方式。

在 Linux/MacOS 中，除了官方下载器，也可以使用包管理器安装qt开发环境，该方法需要有一定的命令行基础。

#### Qt的对象生命周期

Qt中的对象生命周期由`QObject`的`parent`属性决定。当一个对象的`parent`被设置为另一个对象时，当父对象被析构时，它的子对象也会被析构。
这种情况下，我们称父对象拥有子对象的所有权（take ownership）。
而大部分Qt对象都是`QObject`的子类，也就是说，所有对象构成了一颗树，我们`delete`其中一个对象时，整颗子树也会被`delete`。

在本项目中，`addWidget`、`addItem`等方法都会掌管对象。具体哪些操作会获得所有权，以及哪些操作会释放所有权、哪些操作会删除对象，需要查阅具体函数的文档。
一般来说，在父对象被删除之前手动删除子对象是最安全的选择。

#### Qt参考文档

* [Qt官方文档](https://doc.qt.io/qt-6/index.html)
* [Qt组件大全](https://doc.qt.io/qt-6/gallery.html)
* [Qt的对象树](https://doc.qt.io/qt-6/objecttrees.html)

### Git使用教程

Git的教程比较多，我们在这里推荐几个：

- [cpp.studio](https://cpp.studio/toolchain/git/)
- 其他教程：
    * [Git工作流和核心原理](https://www.bilibili.com/video/BV1r3411F7kn)：Bilibili视频，约20分钟
    * [Git教程 - 廖雪峰](https://www.liaoxuefeng.com/wiki/896043488029600)：网页，较详细
    * [Git 原理入门（阮一峰）](http://www.ruanyifeng.com/blog/2018/10/git-internals.html)：网页，简要入门教程
- 上传到[清华`git`](https://git.tsinghua.edu.cn/)时登录验证失败怎么办？
    * 参考教程，在[账户设置](https://git.tsinghua.edu.cn/-/user_settings/personal_access_tokens)中添加一个Personal Access Token；
    * 或者在[账户设置](https://git.tsinghua.edu.cn/-/user_settings/keys)中添加一个SSH公钥（推荐）
- 如何更改本网站语言：右上角头像-Preferences-底部Localization-Language-选择“Chinese”，然后点击页面底部的“Save changes”，可以切换到中文版。

初始仓库里除了main分支，还有一个被保护的down分支。如果之后实验的基础代码有更新，我们会把新的版本push到down分支上。

需要更新实验基础代码时，可以直接在网页左侧菜单“代码”-“分支”处创建从down到开发分支(main)的合并请求，也可以参考git相关教程，在本地合并基础代码：

```bash
git checkout main
git fetch origin down
git merge origin/down
```

<details>
<summary>
本项目可能会用到的`git`操作速查表
</summary>

#### 基础操作

以下所有命令中`<word>`需要替换为你自己的内容。

设置用户名和邮箱：
```bash
git config --global user.email "<your email>"
git config --global user.name "<your name>"
# 例：
git config --global user.email "email@example.com"
git config --global user.name "San Zhang"
```

将代码从网上下载至本地：
```bash
git clone <repo-url>
# 例：
git clone https://git.tsinghua.edu.cn/adv-prog/2022/leveldb-sk/
```

进入仓库目录，查看当前仓库状态：
```bash
git status
```

添加文件到暂存区：
```bash
git add <files>
# 例：添加当前目录下的所有文件。“.”表示当前目录。
git add .
```

提交暂存区的文件至版本库：
```bash
git commit -m "<your message>"
# 例：
git commit -m "Create a new file"
```

#### 同步操作

添加一个远程地址：
```bash
git remote add <remote_name> <remote_url>
# 例：
git remote add upstream https://git.tsinghua.edu.cn/adv-prog/2022/leveldb-sk/
```

推送版本库的文件至远程仓库（如清华`git`）：
```bash
git push <remote> <branch>
# 例：
git push origin main
```

从远程库中下载更新：
```bash
git fetch origin main
git merge origin/main # 合并origin远程的main分支到本地的当前分支
# 或将两步合为一步：
git pull
```

#### 分支操作

创建一个新分支：
```bash
git branch <branch_name>
# 例：
git branch patch_1
```

切换到某分支：
```bash
git checkout <branch_name>
# 例：
git checkout patch_1
# 切换回来main分支：
git checkout main
```

</details>

### 编译运行

1. 参考[课前准备教程](https://meeting.tencent.com/crm/lR9GLWENe4)，安装 Cursor / VSCode，安装推荐扩展，使用 IDE 将代码仓库克隆到本地，并打开项目。
   - 推荐扩展：
     - MS-CEINTL.vscode-language-pack-zh-hans
     - ms-vscode.cpptools-extension-pack
     - theqtcompany.qt-cpp-pack
     - Gruntfuggly.todo-tree
     - eamodio.gitlens
   - Clone with ssh: `git clone git@git.tsinghua.edu.cn:adv-prog/2024/lab2-xxxx.git lab2`
   - Clone with https: `git clone https://git.tsinghua.edu.cn/adv-prog/2024/lab2-xxxx.git lab2`

**.vscode/tasks.json通过工作目录名寻找.pro项目文件，如果使用vscode/cursor作为编辑器，请确保文件夹名称为lab2**

2. 在项目根目录下创建一个build文件夹：
   1. 打开命令面板（Windows/Linux快捷键：`Ctrl+Shift+P` ，MacOS快捷键：`Cmd+Shift+P`）；
   2. 输入 `tasks: run task` 并运行此命令；
   3. 选择 `mkdir` 任务并运行。

3. 运行qmake生成Makefile:
   1. 打开命令面板（Windows/Linux快捷键：`Ctrl+Shift+P` ，MacOS快捷键：`Cmd+Shift+P`）；
   2. 输入 `tasks: run task` 并运行此命令；
   3. 选择 `qmake-release` 任务并运行。

4. 使用Makefile编译项目:
   1. 打开命令面板（Windows/Linux快捷键：`Ctrl+Shift+P` ，MacOS快捷键：`Cmd+Shift+P`）；
   2. 输入 `tasks: run task` 并运行此命令；
   3. 选择 `make-release` 任务并运行。

5. 运行项目:
   1. 打开命令面板（Windows/Linux快捷键：`Ctrl+Shift+P` ，MacOS快捷键：`Cmd+Shift+P`）；
   2. 输入 `tasks: run task` 并运行此命令；
   3. 选择 `run-release` 任务并运行。

#### 注意事项

- 步骤2只需要运行一次，也就是只需要创建一次build文件夹。
- 步骤3-5可以直接通过运行步骤5来实现，也就是直接运行 `run-release` 任务。
  - 因为配置了 `run-release` 依赖于 `make-release` ， `make-release` 依赖于 `qmake-release` 
  - 所以 `run-release` 会自动执行 `qmake-release` 和 `make-release` 任务
- 如出现编译运行的问题且长时间未解决，可尝试将build文件夹删除后重新执行上述步骤2-5。

## lab2 内容

- 学习并熟悉 Qt 框架
- 实现检测并消除连续三个及以上同色球的功能，即完成`Game.cpp`中的`void Game::checkMatches()`函数，要求能够实现连续消除
  - 完成这一步，你将获得一个能够正常运行和游玩的祖玛游戏，但是仍然不会通过CI测试，因为CI测试中会检查链表的实现情况
- 将项目中的数组改为链表实现，也就是将所有涉及到 `Game` 类的 `QVector<Ball> balls;` 的代码改为用 `BallList ballList;` 实现
  - 大部分需要大家修改的代码已经用 `TODO` 标记出来了，未被标记的但仍在修改范围内的代码也可适当修改，可修改的文件包括：
    - `CollisionSystem.cpp`
    - `CollisionSystem.h`
    - `Game.cpp`
    - `Game.h`
    - `GameWidget.cpp`
  - `BallList` 类在 `Game.h` 中定义，是助教提前写好的接口，你可以添加 `BallList` 类的成员变量和函数，但是不可以修改或删去 `BallList` 类已有的成员变量和函数
  - 不需要修改所有涉及到 `Game` 类的 `QVector<Ball> shootingBalls;` 的代码
  - 在修改代码时，你可能需要修改一些函数接口，例如在 `CollisionSystem.h` 中，你需要将 `bool checkPathCollisions(const Ball& shootingBall, QVector<Ball>& pathBalls, const Path& path);` 修改为 `bool checkPathCollisions(const Ball& shootingBall, BallList& ballList, const Path& path);`
  - 完成这一步，你将获得一个能够正常运行和游玩的祖玛游戏，并且能够通过CI测试

### 关于CI

持续集成（Continuous Integration）系统会在每次代码推送后自动执行。

本仓库的持续集成模块提供以下功能：

- 检查程序是否包含语法错误
- 生成Windows可执行程序

生成的windows可执行程序可以在页面左侧的菜单栏中，通过“构建”-“产物”选项被浏览或下载。
