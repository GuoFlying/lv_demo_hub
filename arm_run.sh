###
 # @Author: Flying
 # @Date: 2022-03-27 11:48:31
 # @LastEditors: Flying
 # @LastEditTime: 2022-07-20 20:10:01
 # @Description: 新建文件
### 
nolog_op=""
is_cp_knx="cpknx"
for param in "$@"
do
    if [ "$param" == "nolog" ]; then
        nolog_op="nolog"
    fi

done


export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./resource/lib
chmod a+x ./lv_demo_hub

#sd卡无法运行bug
cp ./resource/lib/libfreetype.so.6.18.0 ./resource/lib/libfreetype.so.6
cp ./resource/lib/librlottie.so.0.2 ./resource/lib/librlottie.so.0

#清理缓存：临时
echo  3 > /proc/sys/vm/drop_caches

if [[ "$nolog_op" == "nolog" ]]
then
    ./lv_demo_hub $2 >>/dev/null 2>&1
else
    ./lv_demo_hub $1
fi
