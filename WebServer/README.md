# WebServer
web server written in C++ 20 using io_uring and corutines


## Benchmarks
**Hardware:** Ryzen 7 6800H (16 threads)
**Tool:** rewrk -t 16 -c 1000 -d 35s
**Response:** Micro-response (~42-182 bytes)

| Metric | My Server (C++20 + io_uring) | nginx | Difference |
|--------|-------------------------------|-------|------------|
| **Requests Per Second (RPS)** | 218,931 | 219,365 | **+0.2%** (nginx) |
| **Avg Latency** | 4.30 ms | 4.55 ms | **+5.8%** (my) |
| **Stdev Latency** | 3.02 ms | 3.01 ms | **+0.3%** (nginx) |
| **Max Latency** | 116.00 ms | 74.97 ms | **+54.7%** (nginx) |
| **Transfer Rate** | 9.19 MB/s | 39.12 MB/s | **+325.7%** (nginx) |

---

### Summary

| Aspect | Winner | Advantage |
|--------|--------|----------|
| Throughput (RPS) | nginx | +0.2% (negligible) |
| Average Latency | My Server | **5.8% faster** |
| Max Latency | nginx | **35% lower** |
| Stability (Stdev) | Tie | 3.01-3.02 ms |
| Data Transfer | nginx | 4.3x more data |

---
