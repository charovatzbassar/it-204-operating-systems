while true; do
	
    read -p "$(hostname)@$(whoami):~$ " input

    if [ "$input" == "exit" ]; then
        echo "Exiting shell interface."
        break
    fi

    # Execute the command
    eval $input
done
