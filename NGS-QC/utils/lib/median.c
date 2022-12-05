
void swap(unsigned int *a, unsigned int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}


void minHeapify(unsigned int a[], unsigned int size, unsigned int i) {
    unsigned int l = 2*i;
    unsigned int r = 2*i+1;
    unsigned int smallest = i;

    if(l<size && a[l]<a[smallest])
        smallest = l;
    if(r<size && a[r]<a[smallest])
        smallest = r;
    if(smallest!=i) {
        swap(&a[i], &a[smallest]);
        minHeapify(a, size, smallest);
    }
}


void buildMinHeap(unsigned int a[], unsigned int size) {
    for(int i=size/2;i>=0;i--)
        minHeapify(a, size, i);
}


int kthLargest(unsigned int a[], unsigned int size, unsigned int k) {
    unsigned int minHeap[k];
    unsigned int i;

    for(i=0;i<k;i++)
        minHeap[i] = a[i];

    buildMinHeap(minHeap,k);
    for(i=k; i<size; i++) {
        if(a[i]>minHeap[0]) {
            minHeap[0]=a[i];
            minHeapify(minHeap, k, 0);
        }
    }
    return minHeap[0];
}


unsigned int median(int l, unsigned int * p, unsigned int kthmin) {
    return kthLargest(p, l, kthmin);
}

