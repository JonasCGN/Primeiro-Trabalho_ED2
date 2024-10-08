#pragma once

#include "./arvore_nota.h"
#include "./arvore_matricula.h"

typedef struct aluno{
    int matricula;
    char nomeAluno[50];
    int codigoCurso;

    ArvoreNota* nota;
    ArvoreMatricula* matriculaDisciplina;
}Aluno;

typedef struct listaAluno{
    Aluno aluno;
    struct listaAluno* prox;
}ListaAluno;