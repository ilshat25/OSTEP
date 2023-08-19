import random

class Job:
    def __init__(self, id: int, size: int):
        self.id = id
        self.size = size
    
    def run(self):
        self.size -= 1
    
    def is_finished(self):
        return self.size <= 0

class StrideJob(Job):
    def __init__(self, id: int, size: int):
        super().__init__(id, size)
        self.pass_value = 0
    
    def run(self):
        super().run()
        self.pass_value += 1
    

class BaseScheduler:
    def create_jobs(self, jobsCount: int, jobSize: int):
        self.jobs = { job.id: job for job in [self.create_job(id, jobSize) for id in range(jobsCount)] }
    
    def remove_job(self, id: int):
        if id in self.jobs:
            del self.jobs[id]
    
    def is_finished(self):
        return not self.jobs
    
    def create_job(self, size: int) -> Job:
        raise NotImplementedError('The job creation function need to be implemented')
    
    def get_job_to_execute(self):
        raise NotImplementedError('The job choid function need to be implemented')

    def run(self, jobsCount: int, jobSize: int) -> list[int]:
        time = 0
        finish_times = []
        self.create_jobs(jobsCount, jobSize)
        while not self.is_finished():
            job = self.get_job_to_execute()
            job.run()
            if job.is_finished():
                finish_times.append(time)
                self.remove_job(job.id)
            time += 1
        return finish_times


class LotteryScheduler(BaseScheduler):
    def create_job(self, id: int, size: int) -> Job:
        return Job(id, size)
    
    def get_job_to_execute(self):
        if self.jobs:
            return random.choice(list(self.jobs.values()))
        else:
            return None


class StrideScheduler(BaseScheduler):
    def create_job(self, id: int, size: int) -> Job:
        return StrideJob(id, size)
    
    def get_job_to_execute(self):
        min_pass_job = None
        for job in self.jobs.values():
            if not min_pass_job or job.pass_value < min_pass_job.pass_value:
                min_pass_job = job
        return min_pass_job


if __name__ == '__main__':
    lottery = LotteryScheduler()
    print(lottery.run(2, 100))

    stride = StrideScheduler()
    print(stride.run(2, 100))