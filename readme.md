通过`SVD`分解实现图像的压缩

奇异值数量k通过设定的能量阀值来自动查找

需要使用的库文件有`opencv`

```bash
# 这里通过创造conda虚拟环境来运行

# conda官网：https://anaconda.org/anaconda/conda

conda create --name env
conda activate env
conda install -c conda-forge gcc_linux-64
conda install -c conda-forge opencv

# 编译运行

mkdir build && cd build
cmake ..
make
./compress_image
```

通过上述方式，即可通过`SVD`分解实现对图片的压缩

通过测试，保留前面权重最大的几个特征值，图像的特征
基本能够保留。

<img src="./3.png" style="zoom: 50%;">

<img src="./4.png" style="zoom:;"  >