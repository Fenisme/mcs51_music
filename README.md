# 51单片机音乐盒

mcs51系列单片机实现简单音乐盒。

## 环境要求

- `platformio` 用于编译
- mcs51系列单片机，或`Proteus`仿真软件

## 编译方法

```
python src/make_song.py > src/music.h
pio run
```

## 配置方式
`src/config.h`中包含单片机平台相关的设置，包括蜂鸣器引脚等；

`src/make_song.py`中包含乐曲的乐谱，修改后执行`python src/make_song.py`生成C语言代码，请手动替换`src/song.c`中的部分。

## Keil相关问题
本项目使用`sdcc`作为编译器，不兼容Keil C，如要做适配请注意以下几个方面：

- 头文件 
- 中断函数语法
