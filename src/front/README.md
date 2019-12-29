# Frontend PECE

# Setup
## Copiar o arquivo de ambiente
Copie o arquivo de exemplo `.env.example` para `.env`, por exemplo:

```shell
cp .env.example .env
```


## Criar a network `pece` no Docker
```shell
docker network create pece
```

---

## Rodando o projeto com Docker

### Instalação e compila para ambiente de desenvolvimento
```shell
make install    # Caso haja algum pacote a ser instalado
make run
```

### Docker em modo de desenvolvimento
Para utilizar o projeto rodando dentro de um container (com hot-reloads), basta setar como **true** a 
variável `DOCKER_DEV` no arquivo `.env`

#### Para ver os logs do node
```shell
make logs
```

### Instalação e compila preprando o app para ambientes de produção
```shell
make install    # Caso haja algum pacote a ser instalado
make build
make run
```

---

# Stylys

## Utility first CSS
Usamos o Tailwind CSS para contruir UI componentes usando classes pre-existentes diretamente no HTML
Mais detalhes sobre: https://tailwindcss.com/docs

## Pre processador
O pre processador utilizado é o `Sass` com o compilador `Node Sass`  
Mais detalhes sobre: https://github.com/sass/node-sass

---

# Linter

## ESLint Rules
O ESLint está utilizando o estilo baseado nas regras do `JavaScript Standard Style`  
Mais detalhes sobre: https://standardjs.com/

## ESLint Import Helpers
Esse plugin adiciona uma ordenação na forma que os imports.
Se as importação não tiverem na ordem correta, o editor e o linter mostrará o erro.

É possível fazer com que o editor faça essa ordenação automaticamente:

### VSCODE
Adicionar essa propriedade no arquivo de settings.json
```json
"editor.codeActionsOnSave": {
    "source.fixAll.eslint": true
}
```

### PHP Storm
...


## Lints and fixes files using docker
```shell
make lint
```

---

## Testes

### testes de unidade (JavaScript e Vue componentes)
Está sendo utilizando o `Jest` como framework de testes javascript juntamente com a ferramenta do Vue chamada `vue-test-utils`  
Mais detalhes sobre: https://vue-test-utils.vuejs.org/

### Estrutura e Nomeclatura
- Testes de unidade são executados em arquivos específicos, então, ele deve ficar no mesmo diretório (ao lado);
- Todos os testes de unidade devem ser nomeados com:
  - `nome do (JavaScript ou componentes) testado` + `.test.js`

**Por exemplo:**  
```
| - / components  
| --- Button.vue  
| --- Button.test.js  
```

### Rodando testes unitários

#### Todos os testes
```shell
make test
```

#### Observando testes (watch)
Executa todos os testes quando um arquivo for alterado
```shell
make test-watch
```

**OBS: É possível também configurar seu editor para executar os testes utilizando o jest**

#### Rodar um arquivo específico
```shell
make test-single FILE_MATCH=AppFooter
```

**OBS: `AppFooter` é o nome do arquivo (sem a extensão) que você deseja fazer o teste, o Jest irá procurar por arquivos de teste que que corresponda, nesse caso de exemplo, ele encontrará `AppFooter.test.js`**

### Coverage
Ao rodar os testes é gerado um diretório chamado `coverage` que exibe numa interface gráfica a cobertura de testes da aplicação.
É possível acessar através do `./coverage/index.html`

---

### Testes de integração
Está utilizando o `Cypress`  
Mais detalhes sobre: https://www.cypress.io/

### Estrutura e Nomeclatura
- Testes de integração são executados de uma maneira holistica, testa o componentamento de vários arquivos, ele deve ficar num diretório específico localizado em `test/e2e/integration`;
- Apesar de todos os arquivos JavaScript serem executados dentro do diretório de specs, a convenção de nomeclatura deve ser:
  - `nome da página ou seção testada` + `.spec.js`

**Por exemplo:**  
```
| - / tests
| --- / e2e
| ---- / integration 
| ------ Home.spec.js
```

### Rodando testes end-to-end 
```shell
make e2e
```

### Rodando testes end-to-end com interface gráfica
```
make e2e-open
```

### Configurando testes no editor de código
#### VSCode (Visual Estudio Code)
É possível rodar o teste no momento em que o cria, utilizando a extenção:  
https://github.com/jest-community/vscode-jest

#### PHP Storm
No PHP Storm é possível também executar os testes em tempo real, para mais informações:  
https://www.jetbrains.com/help/phpstorm/running-unit-tests-on-jest.html


**O projeto já está configurado para o funcionamento em ambos os editores;**

---

### Mais customizações do nuxt-config
See [Configuration Reference](https://nuxtjs.org/guide/configuration/).
