import time
import subprocess


in_q = "search_queue.csv"
out_q = "searched.csv"

# Each range is represented by a single integer.
# Each range is range_inc in lenght.
# For a range, n,
# range_inc*(n - 1) + 5 = start





start = 5
range_inc = 2147483640  # range_inc must be divisible by 6
num = 12848751825131232133313313131318907819791
cmd_str = f"./prime_search {num} {start} {range_inc}"
# cmd_str = f"./prime_search.out 12848751825131232133313313131318907819791 101 100000"
# cmd_str = f"./prime_search 1100489 101 100000"
num_procs = 5
procs = []

for i in range(num_procs):
    
    procs.append(subprocess.Popen(cmd_str_i.split(), stdout=subprocess.PIPE))


proc = subprocess.Popen(cmd_str.split(), stdout=subprocess.PIPE)

while (start-1) ** 2 <= num:
    rv = proc.poll()
    if not rv is None:
        if rv:
            print(f"DETECTED NOT PRIME")
            break
        else:
            print("No rv")
        break
    time.sleep(1)

print("Finished")
print(f"stdout: {proc.stdout.read().decode()}")
