rm time.out

# serial
for n in 10 100 1000 10000 100000 1000000 10000000 100000000; do
    echo $n >> time.out
    for i in {1..10}; do
        ./pi $n >> tmp.out
    done
    echo "scale=6;("`paste -s -d+ tmp.out`")"/10 | bc >> time.out
    rm tmp.out
done

# paralel
for n in 10 100 1000 10000 100000 1000000 10000000 100000000; do
    echo $n >> time.out
    for i in {1..10}; do
        ./pi-par $n >> tmp.out
    done
    echo "scale=6;("`paste -s -d+ tmp.out`")"/10 | bc >> time.out
    rm tmp.out
done
