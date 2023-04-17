## 文件IO
   标准C库IO函数: <br/>
   <img width="600" alt="1681716334059" src="https://user-images.githubusercontent.com/86211987/232414336-29666282-f9c3-49ff-af13-335d3b92d3dd.png"><br/>
   区别: 当追求效率时使用标准C库IO函数因为它提供了缓冲区, 可以减少磁盘IO次数; 当追求时效时使用linux IO函数，每调用一次都会进行磁盘IO<br/>
   

## 文件链接
   硬链接(Hard link):ln a b;unlink a b<br/>
   软链接(Soft link):ln -s a b <br/>
