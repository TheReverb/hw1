# Benchmarking the Memory Hierarchy
### Jonah Kohn

In order to understand the latency of memory access from the different cache levels, a program was designed to intentionally create cache misses. This was achieved by the implementation of a linked list, which was randomized in its link order relative to the order of the containing vector. This would, in theory, appropriately confused the cache prefetcher and allow one to understand the access times without optimizations. Linked lists were created in lengths from 2^10 to 2^26, and the latency of looping over the linked list for a significant number of iterations was averaged to create a read time per-byte.

Below, we can see the latency response to increasing buffer sizes:

![alt text][graph]

By my estimation, this graph would predict cache sizes for my processor as follows: L1 - 32Kb, L2 - 256 Kb, L3 - 6 Mb. The magnitude of the increaes at each of these points on the graph, to me, indicates the jump to the corresponding larger cache. The jump at 6 Mb, for example, very accurately depicts the extra time required to access items in DRAM.

The times written in the link via the assignment seem entirely plausible to me, especially when a few unavoidable instruction executions are accounted for. For example, my program shows ~2.5 ns to access an item from an L1 cache. This however, also includes two instructions - assigning the value, and checking whether the value is null. Without these instructions, the loop would be impossible. With a predicted time of ~1 ns to execute an instruction, and ~0.5 ns to read from the L1, 2.5 ns seems spot-on. Additionally, the time required to read from L2 and DRAM follow directly in line with the online predictions.

My processor, a [5th-gen i7-5700HQ](http://www.cpu-world.com/CPUs/Core_i7/Intel-Core%20i7-5700HQ%20Mobile%20processor.html), boasts an L1 size of 32Kb, an L2 size of 256 Kb, and an L3 size of 6 Mb. These numbers fall perfectly in line with the jumps in latency shown in the graph, as well as my predictions. In all, I believe that I'm accurately measuring what I set out to measure, and that my results fall in line with the expected outcomes. 

[graph]: https://github.com/TheReverb/hw1/blob/master/timing.png
