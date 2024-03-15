ctrl_c() {
    echo ""
    exit 1
}


trap ctrl_c SIGINT

while true; do
	
    read -p "$(hostname)@$(whoami):~$ " input

    if [ "$input" == "exit" ]; then
        echo "Exiting shell interface."
        break
    fi

    eval $input
done
