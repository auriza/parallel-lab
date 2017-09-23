---
title: GBPP Praktikum Pemrosesan Paralel
author: Auriza Akbar
date: 2014
---

# Praktikum Pemrosesan Paralel

1. Pemrograman paralel pada Linux
    - multiprocessing (fork)
    - multithreading (pthread)
    - shared memory (OpenMP)
    - distributed memory (OpenMPI)

2. OpenMP: pengenalan
    - sintaks dasar
    - paralelisasi (parallel, num_threads)
    - sinkronisasi (critical, atomic, barrier)

3. OpenMP: paralelisme data
    - pembagian data pada looping (for)
    - skema pembagian data (schedule)
    - reduksi (reduction)

4. OpenMP: paralelisme fungsional
    - pembagian kerja (sections)
    - eksekusi tunggal (master, single)

5. OpenMP: kasus integrasi numerik
    - integrasi numerik mencari nilai phi
    - fungsi omp_get_wtime()
    - perhitungan speedup dan efisiensi

6. OpenMP: kasus pemrosesan citra
    - format citra PGM (ASCII)
    - membaca dan menulis PGM
    - operasi invert, threshold
    - paralelisasi dan perbandingan kinerja

7. OpenMP: kasus deteksi tepi citra
    - konvolusi
    - deteksi tepi
    - paralelisasi dan perbandingan kinerja

--------

8. MPI: pengenalan
    - init, finalize
    - komunikasi point-to-point (send, recv)

9. MPI: komunikasi kolektif
    - broadcast, reduce
    - scatter, gather
    - barrier

10. MPI: kasus integrasi numerik
    - integrasi numerik mencari nilai phi
    - fungsi MPI_Wtime()
    - perhitungan speedup dan efisiensi

11. MPI: kasus perkalian matriks
    - perkalian matriks-vektor dan matriks-matriks
    - perhitungan speedup dan efisiensi

12. MPI: kasus sorting
    - counting sort, merge sort
    - perhitungan speedup dan efisiensi

13. MPI: cluster computing
    - setting cluster MPI pada Linux
    - menjalankan program pada cluster

14. Ujian
    - paralelisasi program sekuensial dengan OpenMP dan MPI
    - menghitung speedup dan efisiensi program
