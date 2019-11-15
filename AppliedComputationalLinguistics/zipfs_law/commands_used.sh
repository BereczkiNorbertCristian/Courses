head -4000 text3.txt | text3_cut.txt
head -4000 text3.txt > text3_cut.txt
wc text3_cut.txt
head -4200 text3.txt > text3_cut.txt
wc text3_cut.txt
head -4500 text3.txt > text3_cut.txt
wc text3_cut.txt
cat text3_cut.txt | tr ' ' '\n' | sed "s/[^[:alpha:]]//g" | sort | uniq -c | sort > pb2_3_full.txt
less pb2_3_full.txt
tail -10 pb2_3_full.txt
ls -la
cat text2.txt | tr ' ' '\n' | sed "s/[^[:alpha:]]//g" | sort | uniq -c | sort | tail -10
cat text1.txt | tr ' ' '\n' | sed "s/[^[:alpha:]]//g" | sort | uniq -c | sort | tail -10
ls -la
