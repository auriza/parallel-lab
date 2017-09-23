rm time.out

# paralel2
for n in 10 100 1000 10000 100000 1000000 10000000 100000000; do
    #echo $n >> time.out
    for i in {1..10}; do
        ./stat-par2 $n | cut -c 15- | tail -1 >> tmp.out
    done
    echo "scale=6;("`paste -s -d+ tmp.out`")"/10 | bc >> time.out
    rm tmp.out
done

# paralel3
for n in 10 100 1000 10000 100000 1000000 10000000 100000000; do
    #echo $n >> time.out
    for i in {1..10}; do
        ./stat-par3 $n | cut -c 15- | tail -1 >> tmp.out
    done
    echo "scale=6;("`paste -s -d+ tmp.out`")"/10 | bc >> time.out
    rm tmp.out
done
