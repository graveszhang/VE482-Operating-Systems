class process:
    def __init__(self):
        self.max = []
        self.allocation = []
        self.need = []
        self.completed = False

    def printstat(self):
        print("Max resources: ", str(self.max))
        print("Allocated resources: ", str(self.allocation))
        print("Need resources: ", str(self.need))


if __name__ == '__main__':
    available = []  # record available resources
    processes = []  # Store all the processes
    process_num = int(input())
    resource_num = int(input())
    for i in range(process_num):
        tmp = process()
        maxstr = input().split()
        allstr = input().split()
        neestr = input().split()
        for j in range(resource_num):
            tmp.max.append(int(maxstr[j]))
            tmp.allocation.append(int(allstr[j]))
            tmp.need.append(int(neestr[j]))
        processes.append(tmp)
    avastr = input().split()
    for i in range(resource_num):
        available.append(int(avastr[i]))

    print("Initialization Completed!")

    ### Testing
    print("process_num: {}".format(process_num))
    print("resource_num: {}".format(resource_num))
    print("available resource: {}".format(str(available)))
    cnt = 0
    for i in processes:
        print("------ Process {} Status -------".format(cnt))
        cnt += 1
        i.printstat()

    ### Banker's algorithm
    print("------ Banker's Algorithm ------")
    complete_process = 0
    while (complete_process < process_num):
        flag = False
        for p in processes:
            if all(j >= 0 for j in [available[i] - p.need[i] for i in range(resource_num)]):
                flag = True
                p.completed = True
                complete_process += 1
                available += p.allocation
        if not flag:
            print('Status: Unsafe')
            exit()
    print("Status: safe")