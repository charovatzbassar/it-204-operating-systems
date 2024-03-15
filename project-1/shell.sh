# Function to handle Ctrl+C
ctrl_c() {
    echo ""
    exit 1
}

# Trap Ctrl+C and call the ctrl_c function
trap ctrl_c SIGINT

while true; do
	
    read -p "$(hostname)@$(whoami):~$ " input

    if [ "$input" == "exit" ]; then
        echo "Exiting shell interface."
        break
    fi

    # Execute the command
    eval $input
done
