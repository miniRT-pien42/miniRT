#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

typedef struct {
  float x,y,z;
} vector_t;

float dot(const vector_t* a, const vector_t* b);
float squared_norm(const vector_t*v);

float norm(const vector_t *v);
float normalize(vector_t* v);

void cross(vector_t* o, const vector_t*a, const vector_t*b);

const char* vector_str(const vector_t*v);

#endif /* VECTOR_UTILS_H */
