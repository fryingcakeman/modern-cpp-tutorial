# Memory Order Seq Cst

先后一致次序
* 编译器和CPU严格遵循源码逻辑流程的先后顺序。
* 在相同的线程上，以该操作为界，其后方的任何操作不得重新排到它前面，前面的任何操作不得排到它后面。
* 处理器之间需要频繁通信，代价较高。