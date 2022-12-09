kernel void floyd(global int *a, int n) {
    int i = get_global_id(0);
    int j = get_global_id(1);
    int ij = i*n+j;
    int ik = i*n+k;
    int kj = k*n+j;
    if (a[ik] + a[kj] < a[ij]) {
        a[ij] = a[ik] + a[kj];
    }
}
