int __nsleep(const struct timespec *req, struct timespec *rem)
{
    struct timespec temp_rem;
    if(nanosleep(req,rem)==-1)
        __nsleep(rem,&temp_rem);
    else
        return 1;
}
 
int msleep(unsigned long milisec)
{
    struct timespec req={0},rem={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    __nsleep(&req,&rem);
    return 1;
}


typedef struct {
  int ServoAngle;
  int SonarValue;
} Measurement;


Measurement *measurements = NULL;
int     num_elements = 0; // Keeps track of the number of elements used
int     num_allocated = 0; // This is essentially how large the array is

int AddMeasurement (Measurement item)
{
        if(num_elements == num_allocated) // Are more refs required?
        {
                // Feel free to change the initial number of refs
                // and the rate at which refs are allocated.
                if (num_allocated == 0)
                        num_allocated = 3; // Start off with 3 refs
                else
                        num_allocated *= 2; // Double the number
                                                    // of refs allocated

                // Make the reallocation transactional
                // by using a temporary variable first
                void *_tmp = realloc(measurements, (num_allocated * sizeof(Measurement)));

                // If the reallocation didn't go so well,
                // inform the user and bail out
                if (!_tmp)
                {
                        fprintf(stderr, "ERROR: Couldn't realloc memory!\n");
                        return(-1);
                }

                // Things are looking good so far
                measurements = (Measurement*)_tmp;
        }

        measurements[num_elements] = item;
        num_elements++;

        return num_elements;
}

int ResetMeasurements()
{
  num_elements = 0;
}