execute(){
	./main ../vid/KTH-Final-0TbZXdhqvA-640.mp4
}
build(){
	[ -d build/ ] && {
		pushd build &> /dev/null;
	} || {
		mkdir build;
		pushd build &> /dev/null;
		cmake .. -Wdev;
	}
	make -j8; STATUS=$?
	popd &> /dev/null;
	[ $STATUS == 0 ] && echo [100%] $(ls -l main) || {
		echo [ERROR] Compilation error.
		rm -f ./main
	}
}
case "$1" in
	"")
		[ -f main ] || build;
		execute
	;;
	e)
		vi -p main.cpp denseflow.cpp denseflow.h CMakeLists.txt
		build;
		execute;
	;;
esac
