# skiplist
> 跳表全称叫做跳跃表，简称跳表。跳表是一个随机化的数据结构，实质就是一种可以进行二分查找的有序链表。跳表在原有的有序链表上面增加了多级索引，通过索引来实现快速查找。跳表不仅能提高搜索性能，同时也可以提高插入和删除操作的性能。

跳表的原理介绍可以参考[《动图带你深入了解——跳跃列表（SkipList）》](https://juejin.cn/post/7015396092351086622)，文章进行了详细的介绍。  
代码参考了[HiWong的实现](https://github.com/HiWong/SkipListPro)，并进行了一些简化，主要是用[二级指针](https://coolshell.cn/articles/8990.html)取代了footer节点。个人感觉将footer节点设置上一个最大默认值，并与key进行比较的做法不是很合适。  
内部使用的是单链表的方式，如果需要使用双向链表，可以参考[begeekmyfriend](https://github.com/begeekmyfriend/skiplist)的实现。  
