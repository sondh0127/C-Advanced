				// ctn = 'y';
				// while(ctn!='n'){
				// 	// Input name of subject
				// 	name = (char*)malloc(sizeof(char) * 10);
				// 	printf("[+] Enter subject:");
				// 	scanf("%s", name);
				// 	id = get_vertex_id(G, name);
				// 	if (id < 0){
				// 		printf("    - Subject does not exist\n");
				// 		free(name);
				// 		break;
				// 	}
				// 	else{
				// 		free(name);
				// 		// Perform topological sort
				// 		// Print all subject before choosen subject
				// 		printf("      - Prerequisite of subject:");
				// 		output = (int*)malloc(sizeof(int)*count_vertices(G));
				// 		get_topological_queue(G, output, &length);

				// 		for(i=0; i < length; i++){
				// 			printf("%s->", get_vertex_val(G, output[i]));
				// 			if(output[i] == id)
				// 				break;
				// 		}
				// 		putchar('\n');
				// 		free(output);								
				// 	}
				// 	printf("do you wanna continue[Y/n]?");
				// 	getchar();
				// 	scanf("%c", &ctn);
				// }