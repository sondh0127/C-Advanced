Array2 *duongdi2(Graph g,int stop){
    Array2 *a;
    Array2 *b;
    int v,i,j,n;
    int output[100];
    JRB node;
    a=(Array2*)malloc(sizeof(Array2));
    a->total=0;
 
    jrb_traverse(node,g.vertices){
        v=jval_i(node->key);
        n= in_degree(g,v,output);
        if(n==0 && v!=stop){
            //printf("v1=%d\n",v);
            //printf("v2=%d\n",stop);
            b=(Array2*)malloc(sizeof(Array2));
            b=duongdi(g,v,stop);
            //printf("Total=%d\n",b->total);
            if(b->total!=0){
                for(i=0;i<b->total;i++){
                    for(j=0;j<b->B[i].num;j++){
                        a->B[a->total].A[j]=b->B[i].A[j];
                    }
                    a->B[a->total].num=b->B[i].num;
                    a->B[a->total].weight=b->B[i].weight;
                    a->total++;

                }
            }
            free(b);
        }
    }
    return a;

}


Array2 *duongdi(Graph g,int start,int stop){
    Array2 *a;
    Array2 *b;
    int *output;
    int n,i,j,k;
    a=(Array2*)malloc(sizeof(Array2));
    a->total=1;
    a->B[0].num=1;
    a->B[0].A[0]=start;
    output=(int*)malloc(sizeof(int)*100);
    n=out_degree(g,start,output);
    for(i=0;i<n;i++){
        duongdi_a(g,a,start,output[i],stop);
    }
    if(a->total==1 &&  a->B[0].num==1){
            a->total=0;
            return a;
        }   
    if(stop==-1){
        for(i=0;i<a->total;i++){
            a->B[i].weight=0;
            for(j=0;j<a->B[i].num-1;j++){
                a->B[i].weight+=get_edge_weight(g,a->B[i].A[j],a->B[i].A[j+1]);
            }
        }
        return a;
    }
    else{
        k=0;
        b=(Array2*)malloc(sizeof(Array2));
        for(i=0;i<a->total;i++){
            if(a->B[i].A[a->B[i].num-1]==stop){
                for(j=0;j<a->B[i].num;j++){
                    b->B[k].A[j]=a->B[i].A[j];
                }
                b->B[k].num=a->B[i].num;
                k++;
                b->total=k;
            }            
        }
        for(i=0;i<b->total;i++){
            b->B[i].weight=0;
            for(j=0;j<b->B[i].num-1;j++){
                b->B[i].weight+=get_edge_weight(g,b->B[i].A[j],b->B[i].A[j+1]);
            }
        }
        return b;
    }

}

void duongdi_a(Graph g,Array2 *a,int v1,int v2,int stop){
    //Neu v1 la phan tu cuoi cung cua duong di(num-1) va v2 khong co trong duong di cuoi cung thi them v2 vao cuoi duong di va de qui 
    //voi v2 va cac dinh co ket noi den v2.
    //Neu v1 la phan tu gan cuoi cung cua duong di(num-2) va v2 khong co trong duong di thi tang so luong duong di len 1 va cac node
    //trong duong di lay tu num-2 node cua duong di dang truoc va v2
    int i,j,check,check1,n;
    int output[100];
    if((*a).B[(*a).total-1].A[(*a).B[(*a).total-1].num-1]==v1){//phan tu cuoi cung cua mang la v1
        check=0;
        for(i=0;i<(*a).B[(*a).total-1].num;i++){
            if((*a).B[(*a).total-1].A[i]==v2){
                check=1;//v2 co trong mang
                break;
            }
        }
        //them node vao duong di
        if(check==0){
            (*a).B[(*a).total-1].A[(*a).B[(*a).total-1].num]=v2;
            (*a).B[(*a).total-1].num++;
            if(stop==-1){
                n=out_degree(g,v2,output);
                for(i=0;i<n;i++) duongdi_a(g,a,v2,output[i],stop);
            }
            else{
                if(v2!=stop){
                    n=out_degree(g,v2,output);
                    for(i=0;i<n;i++) duongdi_a(g,a,v2,output[i],stop);
                }
            }            
        }
    }
    else{
        check=0;
        for(i=0;i<(*a).B[(*a).total-1].num;i++){
            if((*a).B[(*a).total-1].A[i]==v1){
                check=1;
                break;
            }
        }
        //them duong di moi
        if(check==1){
            check1=0;
            for(j=0;j<i;j++){
                if((*a).B[(*a).total-1].A[j]==v2){
                    check1=1;
                    break;
                }
            }
            if(check1==0){
                (*a).total++;
                for(j=0;j<=i;j++){
                    (*a).B[(*a).total-1].A[j]=(*a).B[(*a).total-2].A[j];
                    (*a).B[(*a).total-1].num=j+1;
                }
                (*a).B[(*a).total-1].A[(*a).B[(*a).total-1].num]=v2;
                (*a).B[(*a).total-1].num++;
                if(stop==-1){
                n=out_degree(g,v2,output);
                for(i=0;i<n;i++) duongdi_a(g,a,v2,output[i],stop);
                }
                else{
                    if(v2!=stop){
                        n=out_degree(g,v2,output);
                        for(i=0;i<n;i++) duongdi_a(g,a,v2,output[i],stop);
                    }
                }   
            }
        }
    }
}

