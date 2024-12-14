# armfly_study

安富莱STM32H7HAL库学习

## 1. 用到的工具

- STM32CubeMX
- VSCode
  - EIDE插件
  - C/C++插件

## 2. 用到的硬件

- Windows10
- STM32F407ZGT6核心板
- STLink
- 1.54存TFT屏

## 3. 目录结构

- Demos (例程目录)
  - bsp_key (例程)
- Document (参考文档目录)
  - 硬件资料

## 4. 项目结构

- bsp_key(项目顶层)
  - 1_App(应用层)
  - 2_Modules(模块层,芯片应用封装)
  - 3_Components(组件层,MCU外设集合封装)
  - 4_BSP(板级支持包,MCU外设底层封装)
  - 5_Core(HAL库层，CubeMX生成的代码)
  - 6_Test(测试层,写测试代码用)
  - 7_Drivers(系统层,不用动)
  - 8_MDK-ARM(MDK工程,不用动)

## 3. 例程说明

### 3.1 demo01_

    跑马灯案例

### 3.2 demo02_

    按键输入案例

## 4. 编程规范
