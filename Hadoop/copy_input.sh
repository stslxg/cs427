#! /bin/bash

for i in {0..390}
do
    if /srv/hadoop/bin/hdfs dfs -test -e "/user/huangxuangui/in/wiki_${i}.txt"
    then
	echo "${i}"
    else
	/srv/hadoop/bin/hdfs dfs -copyFromLocal "/media/tmp/wiki/enwiki/wiki_${i}.txt" "/user/huangxuangui/in/wiki_${i}.txt"
    fi
done