# 21a-emb-aps1

Embarcados - APS 1 - Musical!

Para maiores informações acesse:

https://insper.github.io/ComputacaoEmbarcada/APS-1-Musical/

Issues serão abertos neste repositório para guiar o desenvolvimento
da dupla. **Vocês não devem fechar os issues, apenas a equipe de professores!**, porém devem referenciar nos commits quando um issue 
foi concluído! Isso gerará um PR no classroom que será avaliado pela equipe.

## Documentação

TODO: Aualizar pinos

| Função  | PINO (ex: PA11) |
|---------|-----------------|
| BUZZER  |      PD 20      |
| START   |      PC 31      |
| SELEÇÃO |      PA 19      |

No projeto, desenvolvemos um sistema embarcado capaz de tocar uma melodia monofônica. Para essa tarefa, utilizamos um buzzer, que conectamos diretamente a um pino específico do nosso microcontrolador.
Na estruturação do código do projeto, dividi o código em quatro segmentos distintos, visando uma maior organização e legibilidade:

main.c: Onde toda a lógica principal é executada.
musicas.h: Neste arquivo, armazenei as variáveis correspondentes às três melodias escolhidas, funcionando como uma biblioteca para as composições musicais.
funcoes.c: Aqui, estão centralizadas todas as funções operacionais do sistema, desde a troca de músicas até funções de play/pausa.
funcoes.h: Este arquivo tem a definição de todas as funções, além de estabelecer os pinos do buzzer, botões e LEDs.

### Imagem da montagem

!()![APS 1 - FOTO](https://github.com/insper-classroom/23b-emb-aps-1-aps1-lucasgurgel/assets/81190013/d41c9a84-363f-4acb-8b29-39021937d036)


### Vídeo do projeto

(https://youtu.be/kXgwHfPnINg?si=_6f_GSenbjSo2xom)

### Vídeo da ISSUE 4 - Validação do Buzzer Test

https://www.youtube.com/shorts/3knSFznx1eg

### Músicas e Direitos autorais

TODO: Listar músicas e dar crédio da onde saiu:
Primeira Música: Harry Potter 
Segunda Música: Super Mario Bros
Terceira Música: Merry Christmas 
Todas as músicas foram retiradas do repositório: https://github.com/robsoncouto/arduino-songs
