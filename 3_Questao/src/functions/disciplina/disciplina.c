#include <stdio.h>
#include <stdlib.h>

#include "./disciplina.h"

void cadastrarDisciplina(ArvoreCurso **arvoreCurso){
    ArvoreCurso *curso;
    curso = NULL;
    int cod;

    printf("Digite o codigo do curso:");
    scanf("%d", &cod);
    setbuf(stdin,NULL);
    
    curso = retornaCursoCod(*arvoreCurso, cod);
    if(curso != NULL){
        Disciplina novo;

        printf("Digite o codigo da disciplina:");
        scanf("%d", &novo.codDisciplina);
        setbuf(stdin,NULL);

        printf("Digite o nome da disciplina:");
        fgets(novo.nomeDisciplina,sizeof(novo.nomeDisciplina),stdin);

        setbuf(stdin,NULL);

        printf("Digite a carga horaria da disciplina:");
        do{
            scanf("%d",&(novo.cargaHoraria));
            if(novo.cargaHoraria % 15 != 0){
                printf("\nDigite um numero multiplo de 15:");
            }
        }while(novo.cargaHoraria % 15 != 0 || (novo.cargaHoraria < 30 || novo.cargaHoraria > 90));
        setbuf(stdin,NULL);

        printf("Digite o periodo da disciplina:");
        do{
            scanf("%d", &(novo.periodo));
            setbuf(stdin,NULL);
    
            if(novo.periodo < 1 || novo.periodo > curso->curso.quantPeriodo){
                printf("Digite um periodo valido");
            }
        }while(novo.periodo < 1 || novo.periodo > curso->curso.quantPeriodo);
        
        if(inserirDisciplina(&(curso->disciplina), novo)){
            printf("A disciplina foi cadastrada com sucesso!\n");
        }else{
            printf("A disciplina nao pode ser cadastrada pois ja existe!\n");
        }
    }else{
        printf("Curso nao encontrado\n");
    }
    
}

void removerDisciplinaCurso(ArvoreCurso *arvoreCurso,ListaAluno *listaAluno){
    ArvoreCurso *curso;
    int codCurso,codDisciplina;

    printf("Digite o codigo do curso:");
    scanf("%d", &codCurso);

    curso = retornaCursoCod(arvoreCurso,codCurso);

    if(curso){
        printf("Digite o codigo da disciplina que deseja remover:");
        scanf("%d", &codDisciplina);

        if(verificaMatriculadoDisciplina(listaAluno, codDisciplina)){
            printf("Nao pode remover essa disciplina pois tem aluno matriculada na mesma!\n");
        }else{
            if(verificaDisciplinaNotaAlunos(listaAluno,codDisciplina)){
                printf("Nao pode remover essa disciplina pois tem aluno que cursou na mesma!\n");
            }else{
                if(removerDisciplina(&(curso->disciplina),codDisciplina)){
                    printf("Disciplina removido com sucesso!\n");
                }else{
                    printf("Disciplina nao encontrado!\n");
                }
            }
            
        }
    }
}

void exibirInfoDisciplina(Disciplina disciplina){
    printf("Codigo da Disciplina: %d\n", disciplina.codDisciplina);
    printf("Nome da Disciplina: %s\n", disciplina.nomeDisciplina);
    printf("Periodo: %d\n", disciplina.periodo);
    printf("Carga Horaria da Disciplina: %d\n", disciplina.cargaHoraria);
}

void percorreArvoreDisciplina(ArvoreDisciplina *arvoreDisciplina){
    if(arvoreDisciplina != NULL){
        percorreArvoreDisciplina(arvoreDisciplina->esq);
        exibirInfoDisciplina(arvoreDisciplina->disciplina);
        percorreArvoreDisciplina(arvoreDisciplina->dir);
    }
}

void mostrarDisciplinasCurso(ArvoreCurso *arvoreCurso, int cod){
    if(arvoreCurso != NULL){
        if(cod == arvoreCurso->curso.codCurso){
            percorreArvoreDisciplina(arvoreCurso->disciplina);
        }else if(cod < arvoreCurso->curso.codCurso){
            mostrarDisciplinasCurso(arvoreCurso->esq,cod);
        }else{
            mostrarDisciplinasCurso(arvoreCurso->dir,cod);
        }
    }
}

int verificaDisciplina(ArvoreDisciplina *arvoreDisciplina, int codDisciplina){
    int exist = 0;
    
    if(arvoreDisciplina){
        if(arvoreDisciplina->disciplina.codDisciplina == codDisciplina){
            exist = 1;
        }else if(codDisciplina < arvoreDisciplina->disciplina.codDisciplina){
            exist = verificaDisciplina(arvoreDisciplina->esq,codDisciplina);
        }else{
            exist = verificaDisciplina(arvoreDisciplina->dir,codDisciplina);
        }
    }
    

    return exist;
}

//Percorre as disciplinas de um periodo
void disciplinaPeriodoCurso(ArvoreDisciplina *arvoreDisciplina, int periodo){
    if(arvoreDisciplina != NULL){
        if(periodo == arvoreDisciplina->disciplina.periodo){
            exibirInfoDisciplina(arvoreDisciplina->disciplina);
        }else if(periodo < arvoreDisciplina->disciplina.periodo){
            disciplinaPeriodoCurso(arvoreDisciplina->esq,periodo);
        }else{
            disciplinaPeriodoCurso(arvoreDisciplina->dir,periodo);
        }
    }
}

void mostraDisciplinaPeriodoCurso(ArvoreCurso *arvoreCurso, int cod,int periodo){
    ArvoreCurso *curso;
    curso = retornaCursoCod(arvoreCurso,cod);
    for(int i = 1;i <= curso->curso.quantPeriodo;i++){
        disciplinaPeriodoCurso(curso->disciplina,periodo);
    }
}

void mostrarInfoDisciplina(ArvoreDisciplina *arvoreDisciplina,int codDisciplina){
    if(arvoreDisciplina != NULL){
        if(codDisciplina == arvoreDisciplina->disciplina.codDisciplina){
            exibirInfoDisciplina(arvoreDisciplina->disciplina);
        }else if(codDisciplina < arvoreDisciplina->disciplina.codDisciplina){
            mostrarInfoDisciplina(arvoreDisciplina->esq,codDisciplina);
        }else{
            mostrarInfoDisciplina(arvoreDisciplina->dir,codDisciplina);
        }
    }
}

ArvoreDisciplina* retornaDisciplina(ArvoreDisciplina *arvoreDisciplina, int codDisciplina){
    ArvoreDisciplina* exist;
    exist = NULL;

    if(arvoreDisciplina != NULL){

        if(arvoreDisciplina->disciplina.codDisciplina == codDisciplina){
            exist = arvoreDisciplina;
        }else if(codDisciplina < arvoreDisciplina->disciplina.codDisciplina){
            exist = retornaDisciplina(arvoreDisciplina->esq,codDisciplina);
        }else{
            exist = retornaDisciplina(arvoreDisciplina->dir,codDisciplina);
        }
    }

    return exist;
}