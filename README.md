# GeoHash-in-cpp
使用C++实现GeoHash编码
未进行参数合理化检测
  1. L，B为经纬度范围
  2. 由于生成morton码为64位long long，故GeoHash编码长度n不可以超过64 / 5 = 12 余 4
 
 由于编码长度n的奇偶影响到morton码按位交叉顺序，故在for循环中加入了判断，可以把判断提前提高程序运行效率
