# Software Laboratório de Medição
## Passos

### Configuração do LabVIEW

1. Entre [aqui](httpslumen.ni.comnicifptheader_logincontent.xhtmlaction=create&du=https%3A%2F%2Flumen.ni.com%2Fnicif%2Fus%2Fmyaccount%2Fcontent.xhtml%3Fdu%3Dhttps%253A%252F%252Fwww.ni.com%252Fpt-br%252Fmyni%252Fdashboard.html), cadastre uma conta na National Instruments e selecione a atividade de _Estudante_.
2. Após criar a conta, entre [aqui](httpswww.ni.comensupportdownloadssoftware-productsdownload.labview.html#521715), selecione as especificações da sua máquina e a opção _base_, selecione uma versão maior ou igual a 2021, em seguida clique em _Download_.
3. Ao abrir o instalador
    1. Na primeira seleção de compontentes, marque apenas os componentes _LabVIEW_ e _NI-VISA_ a serem instalados, o resto pode desmarcar.
    2. Na segunda seleção, marque apenas _NI Certificates Installer, NI System Configuration Support for LabVIEW_ e todas relacionadas a _NI-VISA_ 
4. Após a finalização da instalação, aparecerá um dialogo pedindo para ativar o software. Selecione _Log in to Activate_, entre com a conta criada no passo 1 e depois clique em _Extend trial_ e depois em _Finish_.
5. Após isso reinicie a maquina como pedido, o labview aparecerá com um executável. Inicie ele e pule qualquer caixa de diálogo pedido para ativar o software (se não quiser comprar é claro).


### Usando o código
1. Primeiro baixe e faça o upload do firmware na sua placa de arduino.
    1. __OBS__: este firmware apenas funcionará em placas arduino com o microcontrolador atmega328p (e.g.     UNO,Nano) devido ao controle específico de registradores deste uC para o uso de temporizações.

2. Depois de ter feito o upload, volte para o labview e abra a VI _medicao.vi_ através de _File -> Open VI_
3. Selecione a porta COM que está o seu arduino, e rode o programa clicanco em _Run_ que está no canto superior esquerdo, é um icone com a seta apontando para a direita.
4. A partir daí as aquisições já estarão sendo feitas.


### Melhorias
Ainda vou adicionar as instruções para mudar o código de processamento de dados no caso do seu projeto diferir do padrão do Dalton.


## Pinagem

| Grandeza  | Canal do ADC |
| ------------- |:-------------:|
| Corrente      | A0     |
| Tensão      | A1     |
| Luminância    | A2     |
| Temperatura | A3 |
## Dúvidas
Vou estar a disposição para te ajudar em qualquer aspecto do uso desse código. Se precisar também posso auxiliar em aspectos de hardware. Estou no grupo da elétrica qualquer coisa.
