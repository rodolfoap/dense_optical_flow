execute(){
	./doflow KTH-Final-0TbZXdhqvA-640.mp4
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
	[ $STATUS == 0 ] && echo [100%] $(ls -l doflow) || echo [ERROR] Compilation error.
}
case "$1" in
	"")
		[ -f doflow ] || build;
		execute
	;;
	e)
		vi -p doflow.cpp CMakeLists.txt
		build;
		execute;
	;;
esac
