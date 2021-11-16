# LearnRTX
基于OpenGL的光线追踪的实验。  
此项目目前暂停更新：为了支持更好的项目结构和支持更多的光照方案，我重新组织了OpenGL渲染器的实现结构  
新的代码项目已移植到：https://github.com/realAYAYA/LearnGI  

# Descriptions
此工程延续LearnOpenGL渲染器代码继续编写，继续加入对：BVH，Octree，BRDF，路径追踪等知识的研究。
感谢这个作者及他的项目成果：https://github.com/petershirley/raytracingthenextweek
我的实验本质上是复现这个项目的功能（本着学习目的，照抄是不可以的，思路和算法相同但代码结构会有不同出入）
力求在GPU中实现光线追踪算法，所以将算法运行在片段着色器，并尽可能通过优化来做到一定程度上的实时性。
研究工作分为几个阶段：
0.想办法将场均数据打包发送到GPU
1.在fragment shader中实现路径追踪，计算光线传播过程和BDRF来生成光照结果。
2.在上面的基础上实现双向路径追踪，提高路径追踪的收敛速度
3.优化加速结构，BVH的遍历，利用着色器构造BVH（难），Octree研究
4.光线步进，求交计算，可见性计算

# 项目结构
运行说明：
1.打开项目后，将项目属性中C++的头文件目录 和 链接库中的链接库目录修改为当前项目所在目录
    -例如：项目放在桌面时，（默认是C:\Users\AYAYA2\source\repos\LearnRTX\LearnRTX\include） 将"\LearnRTX"前面的目录修改为当前项目所在目录
2.编译运行

# 更新动态
-对视窗类进行了大的改动，并更换了stb库（改为SOIL）导致贴图载入出现bug修复中（8.22）
-长时间太零碎就放一边了

# Futrue（未来展望）
·随着学习的慢慢进行，作者意识到光线追踪技术确实难以用于目前显卡硬件的光栅化渲染。但即便不追求光线追踪算法的实时性，当今仍然有其他效果优秀的全局光照技术，例如：UE等使用的 基于距离场的全局光照计算。
·在光线追踪的学习尾期，作者将继续通过书本和网络资源展开对其他当今流行的全局光照技术技术研究并做实验。

# 结果展示(/Results)
![Image text](https://github.com/realAYAYA/LearnRTX/blob/main/Results/ResOnCpu.png)
![Image text](https://github.com/realAYAYA/LearnRTX/blob/main/Results/ResOnGpu1%20.png)
![Image text](https://github.com/realAYAYA/LearnRTX/blob/main/Results/ResOnGpu2.png)
![Image text](https://github.com/realAYAYA/LearnRTX/blob/main/Results/ResOnGpu3.png)
![Image text](https://github.com/realAYAYA/LearnRTX/blob/main/Results/res11.gif)

### 同样基于此渲染器实现的黑洞模拟
![Image text](https://github.com/realAYAYA/LearnRTX/blob/main/Results/blackhole1.png)
![Image text](https://github.com/realAYAYA/LearnRTX/blob/main/Results/blackhole2.png)
