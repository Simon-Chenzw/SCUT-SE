# Introduction
一个运行于命令行的2048，带有一定程度的智能算法  
支持 `Linux` 与 `Windows` ，**不支持WSL**。  
除去以下库外，均为c++标准库
+ `<conio.h>` `<windows.h>` (at windows)
+ `<termios.h>` `<sys/ioctl.h>` (at linux)

是本人`SCUT`课程`高级语言程序设计C++(下)`的大作业  
所有代码储存于 https://github.com/Simon-Chenzw/homework

## Explanation
+ 特点：
    + 彩色界面
    + 内置几种简单的算法解决2048
    + 便捷的新增自己的算法
    + 多线程运行选定算法

+ 用法：
    + git clone
    + 编译本文件（本库内置makefile配置）
    + 运行可执行文件


+ 新增算法教程 (operator.h)：
    ```
    添加自定义Operator派生类教程：
    
        文件：
            新增AI时在本头文件的末尾添加声明，
            再另起额外的cpp文件实现，
            然后修改本头文件中define的operator_list，
            在其后面添加新增派生类的默认构造函数。
    
    
        派生类必须包含以下函数：
            1)默认构造函数
                基类的构造函数为：
                    Operator(const string& oper_name, const int& oper_type = NON_INTERACTIVE_OPER);
                        oper_name为UI中显示的名字
                        oper_type为 INTERACTIVE_OPER 或 NON_INTERACTIVE_OPER 标志着是否是交互式Operator
    
            2)int get_moved(const Board&);
                board为int[4][4]
                返回值为MOVE_U MOVE_D MOVE_L MOVE_R define于gamecore.h
                gamecore.h也含有bool fast_move(Board&,const int& dire);函数 供快速移动Board所用
    
        *** 注意Operator类会存在多个实例，且也会被include进多个文件 ***
    
    
    ```
    可以参见`upmove_oper`类的结构
