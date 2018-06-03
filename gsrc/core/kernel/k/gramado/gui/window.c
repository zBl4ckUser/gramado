/*
 * File: gui\window.c 
 *
 * Descri��o:
 *     Arquivo principal do Window Manager.
 *     Window Manager.
 *     MB - M�dulos inclu�dos no Kernel Base.
 *     Rotinas envolvendo a feitura de janelas.     
 *     Parte da interface gr�fica oferecida em Kernel Mode.
 *     A interface gr�fica oferecida pelo Kernel Base deve ser leve e veloz.
 *
 * Obs: Muitas funcionalidades devem ser iplementadas em user mode e n�o aqui.
 *      aqui devem ficar as fun��es mais primitivas. e outras pra ganhar desempenho
 *      mas n�o tudo. 
 *
 * @todo: Criar uma fun��o que copie o conte�do de um buffer dedicado de janela para
 * o LFB,(FrontBuffer).
 *       
 * In this file:
 * ============
 * +
 * +
 * +
 *
 * Hist�rico:
 *     Vers�o: 1.0, 2013 - Esse arquivo foi criado por Fred Nora.
 *     Vers�o: 1.0, 2014 - Aprimoramento geral das rotinas b�sicas. 
 *     Vers�o: 1.0, 2015 - Revis�o. 
 *     Vers�o: 1.0, 2016 - Revis�o.
 *     ...
 */

 
#include <kernel.h>
 
//int window_getch_lock;
 
// 
// Argumentos passados pelo Boot Loader em head.s. 
//

extern unsigned long kArg1;    //Video Mode.	
extern unsigned long kArg2;	   //LFB - Linear Frame Buffer.
extern unsigned long kArg3;	   //??.
extern unsigned long kArg4;	   //??.	




int 
windowKillTimer( struct window_d *window,
                 int id )
{
    int Status = 0;
	
	if( (void*) window == NULL )
	{
		Status = 1;
		goto fail;
	}else{
		
		if( window->used != 1 ||
		    window->magic != 1234 )
		{
			Status = 1;
		    goto fail;
		}
    
	    //...
	};

fail:
done:	
    return (int) Status;	
};

/*
 *windowSetTimer:
 * 
 */
// A janela receber� uma mensagem MSG_TIMER 
// sempre que o contador chegar a '0'.
// +Essa rotina deve utilizar o driver de timer 
// para conseguir a contagem que precisa.
// #teste, come�aremos contagem simples para teste.
int
windowSetTimer( struct window_d *window, //janela
                int id,                  //id do timer
				int time                //tempo(medida indefinida ainda)
				)
{
    int Status = 0;
	
    //
	// ## Window  ##
	//
	
	if( (void*) window == NULL )
	{
		Status = 1;
		goto fail;
	}else{
		
		if( window->used != 1 ||
		    window->magic != 1234 )
		{
			Status = 1;
		    goto fail;
		}
		
		//Ok.
		// Aqui devemos registra na estrutura 
		// da janela o id do timer e o tempo 
        //desejado. 		
		
		//obs: temos um limite para ids.
		//window->timer[id].id = id;
		//window->timer[id].time = time;
		
		//...
	};
	
	
fail:
done:	
    return (int) Status;
};



/*
  test - queue support *******************************
 */
 
 
 /*
 
#define MAX_ITEMS    4*4
typedef struct circularQueue_s
{
    int     first;
    int     last;
    int     validItems;
    
	//int     data[MAX_ITEMS];
	unsigned long data[MAX_ITEMS];
	
} circularQueue_t;


    unsigned long readValue;
    circularQueue_t   myQueue;

void initializeQueue(circularQueue_t *theQueue);
 
int isEmpty(circularQueue_t *theQueue);
 
int putItem(circularQueue_t *theQueue, unsigned long theItemValue);
 
int getItem(circularQueue_t *theQueue, unsigned long *theItemValue);
 
//void printQueue(circularQueue_t *theQueue);

*/

/*
void initializeQueue(circularQueue_t *theQueue)
{
    int i;
    theQueue->validItems  =  0;
    theQueue->first       =  0;
    theQueue->last        =  0;
    for(i=0; i<MAX_ITEMS; i++)
    {
        theQueue->data[i] = (unsigned long) 0;
    }        
    return;
}
*/

/*
int isEmpty(circularQueue_t *theQueue)
{
    if(theQueue->validItems==0)
        return(1);
    else
        return(0);
}
*/

/*
int putItem(circularQueue_t *theQueue, unsigned long theItemValue)
{
    if(theQueue->validItems>=MAX_ITEMS)
    {
        printf("The queue is full\n");
        printf("You cannot add items\n");
        return(-1);
    }
    else
    {
        theQueue->validItems++;
        theQueue->data[theQueue->last] = (unsigned long) theItemValue;
        theQueue->last = (theQueue->last+1)%MAX_ITEMS;
    }
}
*/

/*
int getItem(circularQueue_t *theQueue, unsigned long *theItemValue)
{
    if(isEmpty(theQueue))
    {
        printf("isempty\n");
        return(-1);
    }
    else
    {
        *theItemValue =  theQueue->data[theQueue->first];
        theQueue->first = (theQueue->first+1)%MAX_ITEMS;
        theQueue->validItems--;
        return(0);
    }
}
*/

/*
void printQueue(circularQueue_t *theQueue)
{
    int aux, aux1;
    aux  = theQueue->first;
    aux1 = theQueue->validItems;
    while(aux1>0)
    {
        printf("Element #%d = %d\n", aux, theQueue->data[aux]);
        aux=(aux+1)%MAX_ITEMS;
        aux1--;
    }
    return;
}
 
*/

/*
 **************************************
*/ 

//retorna o id de uma janela.
int windowGetWindowID( struct window_d *window)
{
	if( (void*) window != NULL )
	{
		if( window->used == 1 && window->magic == 1234 ){
		    return (int) window->id; 	
		}
	};
	
fail:
	return (int) -1;
};


// Pegar o id da janela main.
// Para os aplicativos lidarem com a �rea de trabalho. 
int windowGetMainWindowDescriptor()
{	
	if( (void*) gui == NULL ){
		goto fail;
	}else{
		
		if( (void*) gui->main == NULL ){
		    goto fail;
		}
		return (int) gui->main->id;
	};
	
fail:	
	return (int) -1;
};

/*
 * windowInitializeBrowserSupport:
 *      (KSOC - Kernel Standard Output Container)
 *       gerenciador de ambientes de janelas ... como no caso de window station/desktop/window...
 * s� que com abas.
 *
 *     Inicializa��o do sistema de suporte ao navegador shell.
 * *Importante: Essa rotina ser� bem longa..
 * devemos inicializar todos os recursos que ser�o usados pelo navagador ...
 * O kernel deve criar uma janela uma janela maximizada que ser� o navegador ...
 * deve criar 12 abas que ser�o atendidas atrav�s do procedimento de janelas do sistema.
 * 
 * *Importante: essa rotina deve ser chamada antes de rodar qualquer processo em user mode.
 * portanteo um bom lugar pra essa rotina ser chamada � no final de main.c, antes de dar iretd
 * para a thread idle.
 *
 */
int windowInitializeBrowserSupport()
{
	int i;
	
	printf("Initializing browser support\n");
	
	
	for(i=0; i< TABWINDOW_COUNT_MAX; i++){
		browsertabList[i] = (unsigned long) 0;
	}
	
	BROWSERWINDOW = NULL;
	TABWINDOW = NULL;
	current_tab = 0;
	
	
	//
	// @todo: Inicializar todos os recursos que o navegador vai precisar.
	//
	
	/*Criando a janela do navegador ... isso requer uma ponteiro exclusivo*/
	/*Esse � a janela com moldura onde as abas ser�o criadas.
	Essas abas ser�o janelas filhas da janela do navegador KSOC.*/
	struct window_d *w;
	

    w = (void*) CreateWindow( 3, 0, 0,"KSOC - Kernel Standard Output Container", 
			                             0, 0, 800, 600, 
										 gui->screen, 0, COLOR_WINDOW, 0xC0C0C0 );

    if( (void*) w == NULL ){
	    printf("windowInitializeBrowserSupport:");
		die();
		//refresh_screen();
	    //while(1){};
	}else{
		
		if( w->used != 1 || w->magic != 1234 ){
	        printf("windowInitializeBrowserSupport: fail");
		    die();
			//refresh_screen();
	        //while(1){};			
		}
		
		RegisterWindow(w);
        set_active_window(w);
		SetFocus(w);

        //Ponteiro exclusivo.
        BROWSERWINDOW = (void*) w;		
	};


	/*Criando as estruturas para as 12 abas do navegador.*/	
	/* Criaremos apenas 4 abas ... rotinas de erro perceber�o a as faltantes*/
	/* cada aba tem uma estrutura de aba, um ponteiro par a asua janela dentro da estrutura.*/
	
	struct browser_tab_d *bt; //browser tabs.
	
	
	/*Importante: Come�aremos de 1 pois a aba 0 � a janela gui->screen*/
	for(i=1; i<4; i++)
	{
		bt = (void*) malloc( sizeof(struct browser_tab_d) );
	    if((void*) bt == NULL){
	        printf("erro tab struct");
		    die();
			//refresh_screen();
	        //while(1){};
	    }		
		
		bt->used = 1;
		bt->magic = 1234;
		bt->type = 1;  //do mesmo tipo por enquanto.
		
		bt->name = "TAB NAME";
		bt->view = 1;
		
		//As abas s�o janelas do tipo 1, pop up simples.
		//os tamanhos ser�o revistos.
		//brancas � princ�pio.
		//
		// *Importante: Pintar todas essas janelas sobrepostas demanda tempo 
        // podemos criar janelas minimizadas, que n�o precisam pintar. 		
		//
        w = (void*) CreateWindow( 1, 0, 0,"TAB", 
			                             0, 24, 800, 600-24, 
										 gui->screen, 0, COLOR_WINDOW, COLOR_WINDOW );		
		
	    if((void*) w == NULL){
	        printf(".");
		    die();
			//refresh_screen();
	        //while(1){};
	    }else{   
		    RegisterWindow(w);
		    //...
	    };
	
	    //Ponteiro da janela da aba.
	    bt->window = (void*) w;
		
		bt->next =  NULL;
		
		//salvando o ponteiro para a tab na lista de ponteiros de tab.
		browsertabList[i] = (unsigned long) bt;
	
	}
	

   //
   // Testando uma aba.
   //   
   
    //testando a aba 1.
    bt = (void*) browsertabList[1];
    
	if((void*) bt == NULL){
	    printf("~erro tab struct");
		die();
		//refresh_screen();
	    //while(1){};
	}	   
   
    if( bt->used != 1 || bt->magic != 1234 ){
	    printf("windowInitializeBrowserSupport: bt fail");
		die();		
	}


	//Determinado que a tab 1 � a tab atual.
	//Obs; Isso n�o � a janela com o foco de entrada.
    current_tab = 1;
	
	//janela da aba. (a aba propriamente dita.
    w = (void*) bt->window;	

    if( (void*) w == NULL ){
	    printf("windowInitializeBrowserSupport:~fail");
		die();
	}else{
		
	    if( w->used != 1 || w->magic != 1234 ){
	        printf("windowInitializeBrowserSupport: ~fail");
	        die();			
	    }
		
		//Aqui temos uma janela v�lida. Essa janela � uma aba.
		//vamos escrever nela pra testar.
		
		//Ponteiro para a janela da aba atual.
		//Obs: Rotinas que desejam pintar na aba atual usam esse ponteiro.
        TABWINDOW = (void*) w;

        
		//Test: Criando alguns elementos gr�ficos dentro da aba no navegador.
		draw_text( TABWINDOW, 0, 0, COLOR_TEXT, "bt: This is a text on the browser tab number 1");	
        draw_button( TABWINDOW, "bt: Button label 11 11", 1, 11, 11, 56, 24, COLOR_BUTTONFACE); 
		StatusBar( TABWINDOW, "bt: Status bar, string 1", "bt: Status bar, string 2");
	};

	
   //
   // Deve haver muito o que fazer ainda  ...
   //
   
    printf("done.\n");	
	return (int) 0;
}


/*
 * @todo: Talvez aque devamos apenas atualizar a flag de view da janela.
int windowShowWindow(struct window_d *window, int msg);
int windowShowWindow(struct window_d *window, int msg)
{
	int Status;
	
	if( (void*) window == NULL ){
		return (int) 1;
	};
	
	
	switch(cmd)
	{
		case MSG_HIDE:
		case MSG_MAXIMIZE:
		case MSG_RESTORE:
		case MSG_SHOWDEFAULT:
		default:
	}
	
	//@todo: Copiar o conteudo do buffer dedicado para o frontbuffer.
	
	//na estrutura de janela:
	//a vari�vel dedicatedbuffer precisa estar correta.
	//a vari�vel frontbuffer precisa estar correta.
	
	return (int) Status;
}
*/



/*
 * windowSetParent:
 * Atribui uma nova janela mae � uma dada janela filha.
 */
/*
void *windowSetParent(struct window_t *clild, struct window_d *new_parent);
void *windowSetParent(struct window_t *clild, struct window_d *new_parent)
{
	//@implementar.
	//Obs: Se o par�metro new_parent for NULL ent�o a janela principal (main ou desktop) 
	//ser� a nova janela mae.
	return NULL;
}
*/

/*
 * windowIsWindow:
 *     Testa atrav�s do handle passado, se � uma janela ou n�o.
 *     0 = Yes; 1 = Not; 
 */
/* 
int windowIsWindow(struct window_d *window);
int windowIsWindow(struct window_d *window)
{
	//@todo:Implementar.
	return 0;
};
*/

/*
void* windowGetWindowWithFocus();
void* windowGetWindowWithFocus()
{
	return (void*) WindowWithFocus;
}
*/

//configuramos qual janela ficar� por cima de todas as outras.
/*
void windowSetForegroundWindow(struct window_d *window);
void windowSetForegroundWindow(struct window_d *window)
{
	//set focus 
	//coloca no topo da lista
	return;
}
*/


//get parent window
void *GetParentWindow(struct window_d * hwnd)
{
	if( (void*) hwnd == NULL ){
		return NULL;
	}
	return (void*) hwnd->parent;
}

//get the desktop of a window.
void *GetWindowDesktop(struct window_d * hwnd)
{
	if( (void*) hwnd == NULL ){
		return NULL;
	}
	return (void*) hwnd->desktop;
};


/*
 * =====================================================
 * windowSetUpColorScheme:
 *     Isso configura os esquemas de cores utilizados 
 * pelo sistema.
 *     Essa rotina � chamada apenas uma vez na inicializa��o
 * do kernel.
 *     O esquema de cores a ser utilizado deve estar 
 * salvo no perfil do usu�rio que fez o logon.
 * Os dois esquemas padr�o chamam-se: 'humility' e 'pride'.
 * + O esquema 'humility' s�o cores com tema cinza, 
 * lembrando interfaces antigas.
 * + O esquema 'pride' s�o cores modernas 
 *   ( Aquele verde e preto e cinza, das primeiras vers�es, 
 * com imagens publicadas. )
 * @todo: � preciso criar rotinas que selecionem entre os 
 * modo criados e habilitados.
 * � preciso criar rotinas que permitam que aplicativos 
 * em user mode criem esquemas de cores e habilite eles.
 */
void windowSetUpColorScheme(int type)
{	
    struct color_scheme_d *humility;
    struct color_scheme_d *pride;	
	
	//
	// * HUMILITY
	//
	
    //Criando o esquema de cores humility. (cinza)
    humility = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) humility == NULL ){
		printf("windowSetUpColorScheme: humility");
		die();
	}else{
		
		//Object.
		humility->objectType = ObjectTypeColorScheme;
		humility->objectClass = ObjectClassGuiObjects;
		

		humility->used = 1;
		humility->magic = 1234;
		humility->name = "Humility";
		
		//Colors
		humility->elements[csiNull] = 0;                               //0
        humility->elements[csiDesktop] = COLOR_BACKGROUND;             //1		
		humility->elements[csiWindow]  = COLOR_WINDOW;                 //2
        humility->elements[csiWindowBackground] = xCOLOR_GRAY1;	       //3	
		humility->elements[csiActiveWindowBorder] = xCOLOR_GRAY2;      //4
        humility->elements[csiInactiveWindowBorder] = xCOLOR_GRAY3;    //5		
		humility->elements[csiActiveWindowTitleBar] = xCOLOR_GRAY2;    //6
        humility->elements[csiInactiveWindowTitleBar] = xCOLOR_GRAY3;  //7	 	
		humility->elements[csiMenuBar] = COLOR_MENUBAR;                //8
        humility->elements[csiScrollBar] = xCOLOR_GRAY3;		       //9  
		humility->elements[csiStatusBar] = COLOR_STATUSBAR;            //10
        humility->elements[csiMessageBox] = xCOLOR_GRAY2;		       //11
		humility->elements[csiSystemFontColor] =   COLOR_BLACK;		   //12
		humility->elements[csiTerminalFontColor] = COLOR_WHITE;	       //13
		//...
		
		//Sanvando na estrutura padr�o para o esquema humility.
		HumilityColorScheme = (void*) humility;
	};	
	
	//
	// * PRIDE 
	//
	
    //Criando o esquema de cores PRIDE. (colorido)
    pride = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) pride == NULL ){
		printf("windowSetUpColorScheme: pride");
		die();
	}else{
		
		//Object.
		pride->objectType = ObjectTypeColorScheme;
		pride->objectClass = ObjectClassGuiObjects;

		pride->used = 1;
		pride->magic = 1234;
		pride->name = "Pride";
		
		//Colors
		pride->elements[csiNull] = 0;
        pride->elements[csiDesktop] = COLOR_BACKGROUND; //0x00808000 verde escuro.
		pride->elements[csiWindow] = COLOR_WINDOW;
        pride->elements[csiWindowBackground] = xCOLOR_GRAY1;
		pride->elements[csiActiveWindowBorder] = 0x0080FFFF; //(LIGHT GREEN) 
        pride->elements[csiInactiveWindowBorder] = 0x0080FFFF;  
		pride->elements[csiActiveWindowTitleBar] = 0x0080FFFF;    
        pride->elements[csiInactiveWindowTitleBar] = 0x0080FFFF;		
		pride->elements[csiMenuBar] = COLOR_GRAY;
        pride->elements[csiScrollBar] = COLOR_GRAY;		
		pride->elements[csiStatusBar] = 0x00404040;  
        pride->elements[csiMessageBox] = COLOR_GRAY;
		pride->elements[csiSystemFontColor] = COLOR_BLACK;    //12
		pride->elements[csiTerminalFontColor] = COLOR_WHITE;  //13		
		//...
		
		//Sanvando na estrutura padr�o para o esquema pride.
		PrideColorScheme = (void*) pride;
	};	
		
	
	//
	// Configurando qual ser� o esquema padr�o.
	//
	
	//
	// @todo; Criar uma fun��o que selecione qual dois esquemas ser�o usados
	//        apenas selecionando o ponteiro da estrutura.  
	//
	
	
    switch(type)
	{
		case ColorSchemeNull:
		    CurrentColorScheme = (void*) humility;
		    break;
		
		case ColorSchemeHumility:
		    CurrentColorScheme = (void*) humility;
		    break;
		
		case ColorSchemePride:
	        CurrentColorScheme = (void*) pride; 
		    break;
		
		default:
		    CurrentColorScheme = (void*) humility;
			break;
	}	
	

done:	
	return;
};

//seleciona o tipo ...isso � um servi�o.
int windowSelectColorScheme( int type )
{
	printf("windowSelectColorScheme: type={%d} \n", type);
	
    switch(type)
	{
		case ColorSchemeHumility:
		    goto do_humility;
		    break;
			
		case ColorSchemePride:
		    goto do_pride;
			break;
			
		default:
		    printf("windowSelectColorScheme: Type not defined\n");
			goto fail;
			break;
	};

	
	
do_humility:
    if( (void *) HumilityColorScheme == NULL )
    {
		printf("HumilityColorScheme fail\n");
        goto fail;     	    	
	}else{
	    if(	HumilityColorScheme->used != 1 || 
		    HumilityColorScheme->magic != 1234 )
		{
			printf("HumilityColorScheme sig fail\n");
			goto fail;
		}
		
		printf("Humility selected\n");
	    CurrentColorScheme = HumilityColorScheme;	
	    goto done;
	};		
	
	
do_pride:	
    if( (void *) PrideColorScheme == NULL )
    {
		printf("PrideColorScheme fail\n");
        goto fail;     	    	
	}else{
	    if(	PrideColorScheme->used != 1 || 
		    PrideColorScheme->magic != 1234 )
		{
			printf("PrideColorScheme sig fail\n");
			goto fail;
		}
		
	    printf("Pride selected\n"); 
		CurrentColorScheme = PrideColorScheme;	
	    goto done;
	};		

done:
    return (int) 0;	
fail:
    printf("fail\n");
    return (int) 1;	    
};


/*
 * windowShowWWFMessageBuffers:
 *     Mostra o buffer de mensagens da janela com foco de entrada.
 *     #Rotinas de teste. @todo: Enviar para a pasta /test.
 *     Esse rotina funcionou e se mostrou bem �til.
 */
void windowShowWWFMessageBuffers()
{
	struct window_d *wFocus;
    wFocus = (void *) windowList[window_with_focus];

	int i;
	//Obs: Tipo.
	for( i=0; i<32; i++){
	    printf("%d ", wFocus->msgList[i]);
    };
    return;	
};


/*
 *****************************************************************************
 * windowSendMessage:
 *    Uma mensagem deve ser enviada para a estrutura da janela com o 
 * foco de entrada.
 *    A classe system.devices.unblocked. pois essa rotina � um m�todo dela.
 *
 * Sobre a fila de mensagem da janela com o foco de entrada:
 * ========================================================
 *  *IMPORTANTE: 
 *      O que importa � qual janela est� com o foco de entrada.
 *      Quando sabemos qual janela est� com o foco de entrada, ent�o
 * sabemos qual � a janela que � a �rea de cliente, sabemos e provavelmente
 * a sua janela m�e � a janela ativa, se ela mesma n�o for a janela ativa.
 *      Uma mensagem pode ser enviada para a janela com o foco de entrada,
 * e a mensagem afetar� apenas a janela com o foco de entrada.
 *      Se a janela que receber a mensagem for a janela ativa, ela n�o
 * ter� janela m�e, nessa caso uma mensagem para fechar uma janela ativa
 * implica em fechar o processo ao qual ela est� vinculada.
 *      (N�o importa qual processo foi interrompido pela interrup��o de 
 * teclado. A mensagem deve ir para a fila de mensagens da janela com o foco
 * de entrada.)
 * @todo: Criar uma rotina semelhante, mas exclusivamente para a janela com
 * foco de entrada.
 * Ex: void windowSendMessageWWW(unsigned long arg1, unsigned long arg2, 
 * unsigned long arg3, unsigned long arg4)
 */	
void windowSendMessage( unsigned long arg1, 
                        unsigned long arg2, 
						unsigned long arg3, 
						unsigned long arg4 )
{    
	struct window_d *wFocus;
	
    //
	// lembrando: O arg1 por enquanto ser� ignorado ;;; ele deveria 
	//conter a janela que devemos enviar a mensagem...
	// pegaremos por conta pr�pria o penteiro pra janela com o foco de entrada.
	//
	
	//
    // N�o estamos falando de fila de mensagens na estrutura da janela,
	// portando se uma mensagem for enviada para uma estrutura de janela
	// ela ir� sobrepor a mensagem antiga caso a mensagem antiga ainda n�o 
	// tenha sido consumida.
    //	
		
	//
	// @todo: 
	// Na verdade, aqui tem que mandar a mensagem para a janela com o foco 
	// de entrada, mesmo que seja uma janela filha.
	//
		
	//lenbrando que esse � um endere�o f�sico, o m�nimo que uma rotina em user mode deve fazer 
    //com essa informa��o � converte-la em endere�o l�gico.
    //Ou devemos enviar um endere�o l�gico ??	
	wFocus = (void *) windowList[window_with_focus];
	
	// Aqui estamos apenas enviando para a janela com foco de entrada.
	// N�o fazer nada caso n�o haja uma janela com o foco de entrada, 
	// pois quem decide que janela tem o foco de entrada � o usu�rio.
		
	if( (void*) wFocus == NULL )
	{
		printf("windowSendMessage: wFocus fail\n");
		refresh_screen();
	    return;
	}else{
		
		//Valida a estrutura da janela com o foco de entrada.
		if( wFocus->used == 1 && wFocus->magic == 1234 )
		{
			
			//ok funcionou
			wFocus->msg_window = (struct window_d *) arg1;
			wFocus->msg   = (int) arg2;      
			wFocus->long1 = (unsigned long) arg3;
			wFocus->long2 = (unsigned long) arg4;
			wFocus->newmessageFlag = 1;
			
			//#bugbug acho que isso n�o � usado.
			//isso � um teste.
			//Para facilitar vamos colocar a mensagem num lugar mais acessivel.
			gNextKeyboardMessage = (int) 0;
			
		}else{
			//fail.
		};
          		
	};
	
	
done:	
	return;
};


/*
 **********************************************************************
 * windowGetHandleWindow:
 *     Pega uma mensagem na estrutura da janela com o foco de entrada.
 *     #importante: N�o devemos nos preocupar em saber qual foi o dispositivo 
 *                  gerador do evento, apenas pegar a mensagem na fila da    
 *                  janela com o foco de entrada.
 *
 * Obs: 
 *     Esse mecanismo deve ser reproduzido para os parametros hwnd, long1 e long2.
 *     As fun��es precisam ser criadas ainda. semelhantes a essa.
 *     Mas o que nos importa agora � somente o par�metro 'msg'.
 * @todo: Quem chamou essa rotina, deseja pegar a mensagem de qualquer janela 
 *ou somente a da janela com o foco de entreada.???
 * @todo: Criar uma rotina semelhante, mas exclusivamente para a janela com foco de entrada.
 * Ex: void *windowGetMessageWWF()
 */

// Salvando a estrutura para o app pegar elemento por eemento.	(#teste)
struct message_d *xxxxsavemessage; 
 
void *windowGetHandleWindow(struct window_d *window)
{
	
	//if( window_getch_lock == 1){
	//	return NULL;
	//}
	
	//#importante.
	//Essa rotina ainda n�o � chamada pelo consumidor,
	//apenas as outras 3.
	
	//@todo: Precisa fazer essa fun��o.
	
//fast_return:
	return NULL;
	
	//fast way 
	//@todo: melhorar isso
	struct window_d *wFocus;
	
	wFocus = (void *) windowList[window_with_focus];
	
	//@todo: habilitar esse if.
	//if( wFocus->newmessageFlag == 0 ){
	//	return NULL;
	//}
	
	return (void*) wFocus->msg_window;
	
	//Nothing.
fail:	
	return NULL;
};


/*
 * windowGetMessage:
 *     Pega uma mensagem na estrutura da janela com o foco de entrada.
 *
 * Obs: 
 *     Esse mecanismo deve ser reproduzido para os parametros hwnd, long1 e long2.
 *     As fun��es precisam ser criadas ainda. semelhantes a essa.
 *     Mas o que nos importa agora � somente o par�metro 'msg'.
 * @todo: Quem chamou essa rotina, deseja pegar a mensagem de qualquer janela 
 *ou somente a da janela com o foco de entreada.???
 * @todo: Criar uma rotina semelhante, mas exclusivamente para a janela com foco de entrada.
 * Ex: void *windowGetMessageWWF()
 */
void *windowGetMessage(struct window_d *window)
{
	unsigned char SC;
	
	
	//if( window_getch_lock == 1){
	//	return NULL;
	//}
	
	
	SC = (unsigned char) keybuffer[keybuffer_head];
	
	//Limpa.
	keybuffer[keybuffer_head] = 0;
	
	keybuffer_head++;
	
	if( keybuffer_head >= 128 ){
	    keybuffer_head = 0;	
	}
		
	//#bugbug
	//alguma coisa est� imprimindo o char duas vezes ...
	//Talvez o pr�prio aplicativo esteja imprimeiro tamb�m.
	//
	
	//Obs: isso alimenta a estrutura da janela com o foco de entrada.
   	//#importante: N�o pode ser tipo 2 pois retornaria um caractere.
	//O tipo 0 coloca a mensgem completa na estrutura do 
	//janela com o foco de entrada.
	//como � tipo 0, ignoraremos o retorno.
	LINE_DISCIPLINE(SC, 0);	
	
	//fast way 
	//@todo: melhorar isso
	struct window_d *wFocus;
	
	wFocus = (void *) windowList[window_with_focus];
	
	if( wFocus->newmessageFlag == 0 ){
		return NULL;
	}
	
	return (void*) wFocus->msg;	
	
	
	//Nothing.
fail:	
	return NULL;
};



void *windowGetLong1(struct window_d *window)
{
	//fast way 
	//@todo: melhorar isso
	struct window_d *wFocus;
	
	
	//if( window_getch_lock == 1){
	//	return NULL;
	//}

	
	wFocus = (void *) windowList[window_with_focus];
	
	if( wFocus->newmessageFlag == 0 ){
		return NULL;
	}
	return (void*) wFocus->long1;
	
	//Nothing.
fail:	
	return NULL;
};



void *windowGetLong2(struct window_d *window)
{
	
	//if( window_getch_lock == 1){
	//	return NULL;
	//}
	
	//@todo: Liberar long2.
	return NULL;
	
	//fast way 
	//@todo: melhorar isso
	struct window_d *wFocus;
	
	wFocus = (void *) windowList[window_with_focus];
	
	if( wFocus->newmessageFlag == 0 ){
		return NULL;
	}
	
	//sinaliza que a mensagem foi lida, e que n�o temos nova mensagem.
	wFocus->newmessageFlag = 0;
	
	return (void*) wFocus->long2;
	

	//Nothing.
fail:	
	return NULL;
};


/*
 * window_getch:
 *
 * Esse � o servi�o 137.
 * Isso � usado pela biblioteca stdio em user mode
 * na fun��o getchar()
 * #bugbug: N�o est� pegando todos os caracteres digitados.
 *
 * um aplicativo que roda no shell pode estar chamando isso.
 *
 */
int window_getch()
{
	unsigned char SC;
	int save;
	
	//pode ser que esse aplicativo n�o tenha janela,
	//mas esteja rodando na janela do shell.
	struct window_d *wFocus;
	
	//
	// Bloqueia pra que nenhum aplicativo pegue mensagens 
	// na estrutura de janela at� que window_getch termine.
	//
	
	//window_getch_lock = 1;
	
	//
	// Pegamos um scancode na fila do teclado,
	// transformamos ela em mensagem e colocamos a 
	// mensagem na estrutura da janela com o foco de entrada.
	//
	

	SC = (unsigned char) keybuffer[keybuffer_head];
	
	//Limpa o offset na fila de teclado 
	//onde pegamos o scancode.
	
	keybuffer[keybuffer_head] = 0;
	
	//Circulamos a fila de teclado.
	keybuffer_head++;
	if( keybuffer_head >= 128 ){
	    keybuffer_head = 0;	
	}

 
	LINE_DISCIPLINE(SC, 0);	

	
 	
	//
	// Agora vamos pegar a somente a parte da mensagem 
	// que nos interessa, que � o caractere armazenado em long1.
	// Obs: Somente queremos o KEYDOWN. Vamos ignorar as outras 
	// digita��es.
	//
	
	//fast way 
	//@todo: melhorar isso
	wFocus = (void *) windowList[window_with_focus];
	if( (void*) wFocus == NULL ){
		//fail 
		//free(wFocus);
		goto fail;
	}else{
		
		if( wFocus->msg != MSG_KEYDOWN ){
		    goto fail;	
		}
		
		save = (int) wFocus->long1;
			
		wFocus->msg_window = 0;
		wFocus->msg = 0;
		wFocus->long1 = 0;
		wFocus->long2 = 0;
			
	    //sinaliza que a mensagem foi lida, e que n�o temos nova mensagem.
	    wFocus->newmessageFlag = 0;
	
	    //window_getch_lock = 0;
		return (int) save;
	};

	
fail:
done:
   // window_getch_lock = 0;
	return (int) -1; //erro	
};



/*
 * windowCreateDedicatedBuffer: 
 *     Cria um buffer dedicado de acordo com as dimens�es da janela.
 */
int windowCreateDedicatedBuffer(struct window_d *window) 
{
	size_t bufferSize;
	
	//Check;
	if((void*) window == NULL ){ 
	    return (int) 1;  //Fail. 
	};
	
    //
    // Buffer size.
    //
	
	//@todo: Usar vari�vel para quantidade de bytes por pixel.
	bufferSize = (size_t) (window->width * 3) + (window->height * 3);
	
	//
	// Alocando mem�ria no Heap do kernel.
	//
	
	if(bufferSize == 0){
	    return (int) 1;    //Fail.	
	}
	else
	{
	    window->DedicatedBuffer = (void*) malloc(bufferSize);	
	    if( (void*) window->DedicatedBuffer == NULL ){
		    return (int) 1;    //Fail.	
		}
		goto done;
	};
	//Nothing
done:
	return (int) 0;  //Success.
};


/*
 * windowLock:
 *     Bloqueia uma janela.
 *     @todo: Quem pode realizar essa opera��o??
 */
void windowLock(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){
	    return;
    };  
    window->locked = (int) WINDOW_LOCKED;  //1.
    return;
};


/*
 * windowUnlock:
 *     Desbloqueia uma janela.
 *     @todo: Quem pode realizar essa opera��o??
 */
void windowUnlock(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){
	    return;
    };  
    window->locked = (int) WINDOW_UNLOCKED;  //0.
    return;
};


/*
 * set_current_window:
 *     @todo: Mudar para windowSetCurrentWindow
 */
void set_current_window(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){ 
	    return; 
	};  
    
	CurrentWindow = (void*) window;
	current_window = (int) window->id;
    return;
};


/*
 * get_current_window: 
 *     Get current window pointer.
 */
void *get_current_window(){
	return (void *) CurrentWindow;
};


/*
int get_current_window_id();
int get_current_window_id()
{
    return (int) current_window;	
};
*/


/*
 * RegisterWindow: 
 *     Registrando uma janela numa lista de janelas.
 */
int RegisterWindow(struct window_d *window)
{
	int Offset = 0; 
    struct window_d *Empty; 
	
    if( (void*) window == NULL ){
        return (int) 1;    //Erro, estrutura inv�lida.
    };
   
	//
	// Contagem de janelas e limites.
	// (� diferente de id, pois id representa a posi��o
	// da janela na lista de janelas).
	//
	
	windows_count++;
	
	if(windows_count >= WINDOW_COUNT_MAX){
	    printf("RegisterWindow: Limits.");
		die();
		//refresh_screen();
		//while(1){}
	};
    
	// Create empty.	
	
//Loop.	
get_next:

	Offset++;
	
	//Limite da lista, volta ao in�cio da lista.
	if(Offset >= WINDOW_COUNT_MAX){
	   Offset = 0;
	};	
    
	//Get empty.
 	Empty = (void*) windowList[Offset]; 	
    if( (void*) Empty != NULL ){
        goto get_next;
    }else{
	    
		//coloca na lista.
		//Onde est� vazio, registra o ponteiro.
	    windowList[Offset] = (unsigned long) window; 	
		
		//configura o id.
		window->id = (int) Offset;
		
		//...
	};  		
	
done:
    return (int) 0;
};


/*
 * windowShowWindowList:
 *     Show Window List
 *     Mostra a lista de janelas registradas. 
 */
void windowShowWindowList()
{
	int i = 0;
	struct window_d *hWnd;
	struct window_d *hWindow;
	
	
	//Se n�o estivermos em modo gr�fico, n�o h� o que mostrar.	
    if(VideoBlock.useGui != 1){
	    return;	
	};
	
	
	//Parent window.
	if( (void*) gui->main == NULL){
	    return;
	};
	
	unsigned long left   = gui->main->left;
	unsigned long top    = gui->main->top;
	unsigned long width  = gui->main->width;
	unsigned long height = gui->main->height;	
	
		
	//@todo: Chamar m�todo.	
	//Cursor.
	g_cursor_x = (left/8);
	g_cursor_y = (top/8);  
	//set_up_cursor(0,10);
	
	//
	// Se estamos no modo gr�fico.
	//
	
	
	//
	// @todo: Usar esquema de cores padr�o.
	//
	
	if(VideoBlock.useGui == 1)
	{
		//Parent window.
	    if( (void*) gui->main == NULL){
	        return;
	    };
			
	    //Create.
	    hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "//KERNEL Window List", 
	                                    left, top, width, height, 
			     				        gui->main, 0, KERNEL_WINDOW_DEFAULT_CLIENTCOLOR, KERNEL_WINDOW_DEFAULT_BGCOLOR ); 

	    if( (void*) hWindow == NULL){
	        printf("show_window_list:\n");
		    return;
        }else{
		    RegisterWindow(hWindow);
			set_active_window(hWindow);
			SetFocus(hWindow);
	    };										
		
		
		// Auterando as margens.
		// Essas margens s�o usadas pela fun��o printf.
		// Obs: As medidas s�o feitas em n�meros de caracteres.
		// Obs: @todo: Devemos usar aqui o ret�ngulo da �rea de cliente,
		// e n�o as margens da janela.
		// A estrutura de janela deve nos oferecer os valores para a m�trica do 
		// ret�ngulo da �rea de cliente.
		// Obs: @todo:Acho que essa n�o � a forma correta de configurar isso. Uma 
		//rotina deveria perceber as dimens�es da janela de do caractere e determinar
		//as margens.
		
		g_cursor_left   = (hWindow->left/8);
		g_cursor_top    = (hWindow->top/8) + 4;   //Queremos o in�cio da �rea de clente.
		g_cursor_right  = g_cursor_left + (width/8);
		g_cursor_bottom = g_cursor_top  + (height/8);
		
		//cursor (0, mas com margem nova).
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 
		
        //Mostrando as informa��es de todas as janelas registradas.		
        while(i < WINDOW_COUNT_MAX)
        {	
	        hWnd = (void*) windowList[i];
		
		    //
		    // @todo: BUGBUG.
		    // O valor de hWnd tem que estar num limite v�lido, n�o adianta apenas ser
		    // diferente de NULL.
		    //
		
		    if( (void*) hWnd != NULL )
			{
	            printf("i={%d} h={%x} dBuf={%x} Name={%s}\n", i, hWnd, hWnd->DedicatedBuffer, hWnd->name);
				//draw_text( hWindow, 8,  1*(400/16), COLOR_WINDOWTEXT, "F1 Help.");
	        };
		    ++i;
	    };
		
		show_active_window();
        show_window_with_focus();
        SetFocus(hWindow);
	
		
		//voltando a margem normal a margem
		g_cursor_left   = (left/8);    //0;
		g_cursor_top    = (top/8);        //0;
		g_cursor_right  = (width/8);   
		g_cursor_bottom = (height/8);  
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top;
        //set_up_cursor(g_cursor_left,g_cursor_top); 		


		StatusBar(hWindow,"Esc=EXIT","Enter=?");		
		//Nothing.
	};	   

    // Continua ...
	
done:
    //@todo; Aqui podemos dar refresh apenas na janela
	refresh_screen();
    //SetFocus(hWindow);
    return;
};


/*
 * redraw_window:
 *     O OBJETICO DESSA ROTINA DEVE SER APENAS REPINTAR UM RET�NGULO
 * QUE FOI PINTADO DENTRO DA �REA DE CLIENTE DA JANELA QUE FOI PASSADA 
 * VIA ARGUMENTO.  @TODO 
 * Obs: Esse ret�ngulo deve pertencer a janela que foi passada por argumento.
 * na estrutura de ret�ngulo deve haver um ponteiro para  ajanela � qual ele pertence.
 * tamb�m deve-se repintar os elementos incluidos na �rea de cliente pelo programa aplicativo.
 * a estrutura de janela deve registrar totos os elementos que foram incluidos na hora da sua cria��o.
 * *****************
 *     Repinta uma janela de acordo com os par�metros na estrutura.
 *     Repinta uma janela v�lida. Tem que estar registrada. 
 *     @todo: Mudar para windowRedrawWindow(.)
 * Obs: Esse � o tipo de rotina que exige o recurso de buffer dedicado.??
 * Pois podemos redezenhar a janela em seu buffer dedicado e depois copiar
 * o conte�do do buffer dedicado para o backbuffer... na hora de atualizar a tela
 * � so copiar o backbuffer no frontbuffer(LFB).

 * pois bem, essa janela vai ter muitos elementos para incluir isso leva muito tempo.
 * Devemos registrar na estrutura da janela todos os bot�es que ela tem.
 * todos os textos gravados nela... todas as cores etc..
 */
//int windowRedrawWindow(struct window_d *window) 
//int redraw_window(struct window_d *window, struct rect_d *rect)
int redraw_window(struct window_d *window)
{
	int Status;  
 
	//Checar se a estrutura � v�lida.
	
	//handle
	if((void*) window == NULL){
		return (int) 1;
	};
	
	//used magic
	if( window->used != 1 || window->magic != 1234 ){
		return (int) 1;
	};
	
	
	//@todo: Pra que serva a flag redraw ??
	// � para indicar que repecisamos repintar. ??
	//if( window->redraw != 1 ){ return (int) 0;}
	
	//
	// Ok, pelo jeito j� temos uma estrutura v�lida.
	//
	
	// Minimized? Se tiver minimizada, n�o precisa repintar.
	//ent�o est� tudo certo?? retorna 0??
	Status = (int) is_window_minimized(window);
    if(Status == 1){
	    return (int) 0;  //??
	};	
	
	//E se ela estiver travada ??
	//O que significa travada?? n�o pode se mover??
	// ?? travada pra quem ??
	//if(window->locked == 1){}
	
	//@todo:
	//docked ?? num canto da tela.

	
	//Pintar ?? Onde ?? backbuffer ?? dedicated buffer ??
//drawWindow:	
	
	// *********************************
	// Devo lembrar que as caracter�sticas da janela est�o salvas na estrutura
	// e s�o muitas caracter�sticas. N�o exige c�lculos, toda a m�trica j� est� pronta.
	// *********************************
	
	
	//Buffers ??
	//window->DedicatedBuffer
	//window->BackBuffer
	//window->FrontBuffer
	
	
	//
	// *Importante: Checando se o esquema de cores est� funcionando.
	//
	
	if( (void*) CurrentColorScheme == NULL ){
		printf("redraw_window: CurrentColorScheme");
		die();
	}else{
		
		if( CurrentColorScheme->used != 1 || CurrentColorScheme->magic != 1234 ){
		    printf("redraw_window: CurrentColorScheme validation");
		    die();			
		};
		//Nothing.
	};	
	
	// ****************************
	// Importante:
	// Agora na hora de efetivamente redezenhar podemos ver na estrutura
	// quais s�o os elementos presentes nela. Lembrando que esses elementos 
	// podem ter sido modificados, ent�o o melhor lugar para pegar essas
	// informa��es � na estrutura mesmo, pois l� ser�o salvos as prefer�ncias
	// atuais do usu�rio em rela��o a janela que deve ser repintada.
	// Ex: O usu�rio pode ter redimencionado ou arrastado elementos da janela,
	// ou ocultado apenas. Afinal, feito escolhas ... usuar�sses.
	//*************************************
	
    //
	// Redraw !
	//	
	
redrawBegin:


	if( window->view == VIEW_NULL ){
		//@todo: temos um problema, dvemos retornar??
	    //return NULL;
	};		

    //Sombra.	
	if(window->shadowUsed == 1)
	{
        drawDataRectangle( window->left +1, 
		                   window->top  +1, 
						   window->width  +1 +1,   // @todo: Adicionar a largura da bordas bordas verticais e barra de rolagem se tiver.
						   window->height +1 +24 +1,   // @todo: Adicionar as larguras das bordas horizontais e da barra de t�tulos.
						   xCOLOR_GRAY1 );         //Cinza escuro.       
	};

    //Background.
	if(window->backgroundUsed == 1)
	{		
	    //if( (unsigned long) type == WT_SIMPLE){
		//    window->color_bg = color;
		//};
		
		//Validando o argumento para todos os tipos de janelas.
		window->color_bg = xCOLOR_GRAY2;  //CINZA UM POUQUINHO MAIS CLARO.
		
		//@todo: Se tiver barra de rolagem a largura do backgrond deve ser maior.
		//if()
		
		//@todo: Passar a estrutura de janela.
		drawDataRectangle( window->left, 
		                   window->top, 
						   window->width,  // @todo: Adicionar a largura da bordas bordas verticais.
						   window->height, // @todo: Adicionar as larguras das bordas horizontais e da barra de t�tulos.
						   window->color_bg );      	
	};
	
	
	
    //T�tulo + borda.	
	if(window->titlebarUsed == 1)
	{ 
		//Focus.
		//Cores diferentes se tiver foco e se n�o tiver.
		if(window->id == window_with_focus){
		    window->color_bg = CurrentColorScheme->elements[csiActiveWindowTitleBar]; 
		}else{
			window->color_bg = CurrentColorScheme->elements[csiInactiveWindowTitleBar]; 
		};
		
		//@todo: String color.
		
		//@todo: String size.
		
		//@todo: Se tiver barra de rolagem, a largura deve ser maior.
		//if()
		
		//Rectangle and string.
		
        drawDataRectangle( window->left, 
		                   window->top, 
						   window->width  +1 +1,  // @todo: Adicionar a largura da bordas bordas verticais.
						   window->height +1 +24 +1, // @todo: Adicionar as larguras das bordas horizontais e da barra de t�tulos.
						   window->color_bg );
						   
		//ressaltando a barra de t�tulos da janala com o foco de entrada.
        //quem deve ser pintada diferente � a janela com o foco de entrada e n�o a janela ativa.
        //Obs: Isso vale para janelas com bordas. 		
        //if(window->id == window_with_focus)
		if(window->id == active_window)
		{
            drawDataRectangle( window->left, 
		                       window->top, 
				    		   window->width  +1 +1,  // largura do ret�ngulo que marca que a janela est� ativa.
						       4,                     // altura do ret�ngulo que marca que a janela est� ativa.
						       COLOR_SALMON );			
		}
						   
		//@todo: Se estivermos em full screen, n�o teremos string.				   
		draw_string( window->left +8 +16 +8, 
		             window->top +8 +4, 
					 COLOR_TEXT,  //*test
					 window->name );  
					 
					 
	    //Isso � um teste.
	    //A janela nem foi registrada ainda e j� estamos passando o handle
	    //via argumento.
		
	    //So criamos o bot�o na barra de t�tulos se tivermos uma barra de t�tulos.
		//ent�o esse � o lugar certo para essa rotina.
		
		//@todo: Se estivermos em full screen, n�o teremos bot�o.	
		if(window->minimizebuttonUsed == 1)
		{
			//Quando passamos o handle da janela, a fun��o draw_button
			//obtem as margens que precisa. nos resta passarmos os 
			//deslocamentos em rela��o �s margens. (x=window->width-?) (y=2).
			//A fun��o draw_button vai somar a margem obtida pelo handle 'window'
			//ao deslocamento obtido em (x=window->width-?).
	        draw_button( window, "V", 1, 
			             (window->width -42 -1), 4, 
						 21, 21, 
						 COLOR_BUTTONFACE);	
	    };
		
		//@todo: Se estivermos em full screen, n�o teremos bot�o.
	    if(window->closebuttonUsed == 1)
		{
	        draw_button( window, "X", 1, 
			            (window->width -21), 4, 
						21, 21, 
						COLOR_BUTTONFACE);				
	    };					 
					
		//More??...			 		 
	};		
	
	

   // Client Area. 	
	if(window->clientAreaUsed == 1)
	{
		//
		// Obs: A Client Area � apenas um ret�ngulo.
		//

		//@todo: Passar a estrutura de janela.
		
		
		//
		// #BUGBUG :: N�O PODEMOS REALOCAR NOVAMENTE ... TEMOS QUE CHECAR 
		// SE A ESTRUTURA � V�LIDA...
		// SE TRATA APENAS DE UMA ESTRUTTURA DE RET�NGULO, N�O ESPERAMOS MUITOS PROBLEMAS.
		//
		
		 
		if( (void*) window->rcClient == NULL )
		{
			printf("redraw_window: a estrututura de client falhou");
			die();
			//refresh_screen();
            //while(1){}			
		     
		}else{
			
			//conferir validade.
			if( window->rcClient->used != 1 || window->rcClient->magic != 1234 ){
			    printf("redraw_window: validade falhou");
			    die();
				//refresh_screen();
                //while(1){}							
			}
		    
            //dimens�es e posicionamento da �rea de cliente.
			//Esse � o posicionamento e as dimens�es da janela propriamente dita.
			//Nesse espa�o ser�o inclu�dos elementos adicionais.
			//Essa � a parte que deve parecer em full screen.
			window->rcClient->x  = (unsigned long)(window->left +1);     //+ borda
            window->rcClient->y  = (unsigned long)(window->top  +1 +24); //+borda +barra de t�tulos.     
            window->rcClient->cx = (unsigned long)(window->width);    
            window->rcClient->cy = (unsigned long)(window->height);	
            
            window->rcClient->width  = (unsigned long) window->rcClient->cx;
            window->rcClient->height = (unsigned long) window->rcClient->cy;
			
            window->rcClient->left   = (unsigned long) window->rcClient->x;
            window->rcClient->top    = (unsigned long) window->rcClient->y;
  			window->rcClient->right  = (unsigned long) (window->rcClient->left + window->rcClient->width);
			window->rcClient->bottom = (unsigned long) (window->rcClient->top + window->rcClient->height);
		
		    //zerando o deslocamento.
		    window->rcClient->x = 0;
			window->rcClient->y = 0;			
			
			//draw
            drawDataRectangle( (unsigned long) window->rcClient->left, 
		                       (unsigned long) window->rcClient->top, 
						       (unsigned long) window->rcClient->width, 
						       (unsigned long) window->rcClient->height, 
						       (unsigned long) window->rcClient->color_bg );         
							    
		};
		//Nothing.
	};




	//
	// Outros elementos ainda n�o implementados ...
	//
	
	//checar na estrutura se essa janela tinha:
	//bot�es ?? bot�es de radio ?? textos ?? barras ??
	//etc ...


	//
	// A rotina de repintura deve estar em sintonia com a rotina de pintura, elas 
	// devem ser semelhantes, porem a rotina de repintura deve levar em considera��o 
	// os elementos inclu�dos depois da cria��o da janela e que ficam gravados na 
	// estrutura. como por exemplo: arquivos abertos.
	//

	//Continua ...
	
done:
    return (int) 0; 
};

/*
 * redraw_screen:
 *     Repinta todas as janelas com base na zorder.
 *     @todo: Obs: Ao repintar cada janela a rotina redraw_window dever� 
 * incluir todos os elementos da janela. Do mesmo jeito que o usu�rio 
 * modificou de acordo com suas prefe�ncias.
 *
 */
int redraw_screen()
{
	int z;
    int RedrawStatus;	
	struct window_d *zWindow;
	
	//
	// Vamos procurar na lista por ponteiros v�lidos.
	// Repintaremos todas as janelas com ponteiros v�lidos.
	//
	
	for( z = 0; z < ZORDER_COUNT_MAX; z++ )
	{
	    zWindow = (void*) zorderList[z];
	
		//Pegando um ponteiro de janela v�lido na zorderList.
		if( (void*) zWindow != NULL )
		{
			if( zWindow->used == 1 && zWindow->magic == 1234 )
            {
				//compara os �ndices.
				if( zWindow->zIndex != z ){
					printf("redraw_screen: z index error\n");
					goto fail;
				};
				
				//retira o foco.
				//KillFocus(zWindow);
				
				//Repinta uma janela.
				RedrawStatus = (int) redraw_window(zWindow);
				if(RedrawStatus == 1){
					printf("redraw_screen: redraw error\n");
					goto fail;
				};
				//Nothing.
			};
        //Nothing.			
		};
       //nothing.
	};	

	//#bugbug ?? Repintaremos duas vezes a �ltima janela.
    // Repintaremos novamente a �ltima janela.
    //Agora com foco de entrada.	

    if( (void*) zWindow != NULL )
	{
		if( zWindow->used == 1 && zWindow->magic == 1234 )
		{
            set_active_window(zWindow);	
            SetFocus(zWindow);

	        //Repinta uma janela.
	        RedrawStatus = (int) redraw_window(zWindow);
	        if(RedrawStatus == 1){
		        printf("redraw_screen: redraw error\n");
		        goto fail;
	        };
		};
	};
	
	
//Seo for terminar corretamente � porque repintamos tudo o que foi poss�vel.	
//Nothing.
done:	
    return (int) 0;	
fail:
    printf("redraw_screen: FAIL.\n");
    die();
	//while(1){}
};



/*
 * resize_window:
 *     Muda as dimens�es da janela.
 */				  
int resize_window(struct window_d *window, unsigned long cx, unsigned long cy)
{
    if( (void*) window == NULL ){
	    return (int) 1;    //Erro, estrutura inv�lida.
	}else{	
	    
		//@todo: Checar limites.
	
        window->width  = (unsigned long) cx;
        window->height = (unsigned long) cy;	
	};

done:
    return (int) 0;
};


/*
 * replace_window:
 *     Muda os valores do posicionamento da janela.
 */				  
int replace_window(struct window_d *window, unsigned long x, unsigned long y)
{
    if( (void*) window == NULL ){
	    return (int) 1;
	}else{
		
        //@todo: Checar limites.
	
        window->left = (unsigned long) x;
        window->top  = (unsigned long) y;
	};

done:
    return (int) 0;
};


/*
 * is_window_full:
 *     Checar se est� no modo tela cheia.
 *
 *     retorno 1, modo tela cheia.
 * @todo: Rever o retorno.
 */
int is_window_full(struct window_d *window)
{
    //Checa estrutura.
    if( (void*) window == NULL ){
	    return (int) 0;    //FALSE.
	};

	//Checa modo tela cheia.
    if(window->view == VIEW_FULL){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;
};


/*
 * is_window_maximized:
 *     Checar se est� no modo maximizado.
 *
 *     retorno 1, modo maximizada.
 * @todo: Rever o retorno.
 */
int is_window_maximized(struct window_d *window)
{
    //Checa estrutura.
    if( (void*) window == NULL){
	    return (int) 0;    //FALSE.
	};

	//Checa se est� maximizada.
    if( window->view == VIEW_MAXIMIZED){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;    //FALSE.
};

//todo: rever o retorno
int is_window_minimized(struct window_d *window)
{
    //Checa estrutura.
	if( (void*) window == NULL){
	    return (int) 0;    //FALSE.
	};

	//Checa se est� minimizada.
    if( window->view == VIEW_MINIMIZED){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;    //FALSE.
};


/*
 * CloseWindow:
 *     Fecha uma janela. (Destr�i).
 *
 *     Obs: O ato de fechar uma janela est� associado
 *          ao ato de encerrar um processo. Mas nem sempre.
 *     *Importante: @todo: Fechar  ajanela qui deve signifcicar apenas 
 * sinalizar para o GC que ele pode atuar sobre a estrutura.
 */
void CloseWindow(struct window_d *window)
{
	int Offset;
	
	//Check.
	if( (void*) window == NULL ){ 
	    return; 
	};
	
	//Obs:
	// N�o fechamos a janela principal.
	//Se for a janela principal.
	//if( (void*) window == (void*) gui->main ){
	//	return;
	//}
	
	//
	// ?? E as threads e processos associados � essa janela ??
	//

	// Focus.
	KillFocus(window);

	
    //Se temos uma janela m�e v�lida. Ela herda o foco.
	if( (void*) window->parent != NULL )
	{
        if( window->parent->used == 1 && window->parent->magic == 1234)
        {			
            set_current_window(window->parent); 
	        set_active_window(window->parent);
            SetFocus(window->parent);
        }; 		
    };
	
	
	//
	// devemos retirar a janela da zorder list 
	//
	
	int z = (int) window->zIndex;
	
	if( z >= 0 && z < ZORDER_COUNT_MAX )
	{
		//retira da lista
	    zorderList[z] = (unsigned long) 0;	
	    
		//atualiza o contador.
        zorderCounter--;
	   
	    if(zorderCounter < 0 ){
		    zorderCounter = 0;
        }
	};
	
	
    //Sinaliza para o GC.
	window->used = WINDOW_GC;       //216;
	window->magic = WINDOW_CLOSED;  //4321;
	
// Done
done:
    return;
};


/*
 * DestroyWindow:
 *     Destr�i uma janela.
 *
 *     Obs: Quando a janela � do tipo Overlapped,
 *          destruir janela significa tamb�m fechar 
 *          o processo e as threads associados � ela.
 *
 *          Pois Overlapped � o tipo de janela usado
 *          como janela principal de um processo.
 *   Obs: Apenas sinalizaremos para o GC.
 */
void DestroyWindow(struct window_d *window){	
    CloseWindow(window);
    return;
};


/*
 * get_active_window:
 *     Obtem o id da janela ativa.
 *     @todo: Mudar para windowGetActiveWindowId().
 */
int get_active_window(){
    return (int) active_window;  
};


/*
 ****************************************************
 * set_active_window:
 *     Seleciona qual ser� a janela ativa.
 *     Ativa uma janela.
 */
void set_active_window(struct window_d *window)
{
	//Check window.
	if((void*) window == NULL ){ 
	    return; 
	}else{

	    if( window->used == 1 && window->magic == 1234 )
		{
		    window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_FOREGROUND;

			//Estrutura global
	        ActiveWindow = (void *) window;

		    //Vari�vel global
            active_window = (int) window->id;				
		}
	};
	//Nothing.
done:
    return;
};


/*
 * change_active_window:
 *     @todo: Trocar a janela ativa
 */
void change_active_window(int id)
{
	// @todo: Limits. Max.
    if(id < 0){
	    return;
	};
	active_window = (int) id;
};


/*
 * show_active_window:
 *     Mostra o id da janela ativa.
 *     @todo: Mudar o nome para windowShowActiveWindowId() 
 */
void show_active_window(){
	printf("ActiveWindowId={%d}\n", (int) active_window);
};

/*
 * show_window_with_focus:
 *     Mostra o id da janela com o foco de entrada..
 */
void show_window_with_focus(){
	printf("wwfId={%d}\n", (int) window_with_focus);
};

/*
 * CloseActiveWindow:
 *     Fecha a janela ativa.
 */
void CloseActiveWindow()
{
	int Offset;
    struct window_d *Window;
	
    Offset = (int) get_active_window();	
	if(Offset < 0){
       return;	
	};
	
	//struct.
	Window = (void*) windowList[Offset];
	
	//Nothing to do.
	if( (void*) Window == NULL ){
        return;
    }else{
	    
		//Torna ativa a pr�xima janela.
	    if( (void*) Window->next != NULL ){
	        set_active_window(Window->next);
	    }else{
	        //Torna ativa a janela m�e.
	        if( (void*) Window->parent != NULL ){
	            set_active_window(Window->parent);
	        };
		};
	};	
	
// Done.
done:
    DestroyWindow(Window);
    return;
};


//
// @todo: windowSetFocus(.) e windowGetFocus() windowSwitchFocus()
//



void windowBlockfocus(){
	gFocusBlocked = (int) 1;
};

void windowUnblockFocus(){
	gFocusBlocked = (int) 0;
};


/*
 *****************************************************
 * SetFocus:
 *     + Seta o foco em uma janela.
 *     + Configura o cursor.
 *     + Reinicia um buffer.
 *           
 * @todo:
 *     Tentando configurar o cursor dentro da �rea de cliente.
 *     Se a janela for o frame de aplicativo, ent�o o cursor 
 *     fica dentro dos limites da �rea de cliente, mesmo que esteja 
 * em full screen.
 *     Se a janela for um editbox, faz mais sentido ainda que 
 * o corsor fique dentro dos limites da �rea de cliente.
 *
 * #importante:
 *  Isso depende do tipo de janela. Se for um editbox tem que colocar o 
 * cursor no in�cio da �rea de edi��o.
 * ...
 */
void SetFocus( struct window_d *window )
{
	
	int i;
	int WindowID;
	
	//Imposs�vel mudar o focus.
	//Isso manter� o foco na janela do desenvolvedor
	//durante a fase de cria��o da interface gr�fica.
	//if( _lockfocus == 1){
	//	return;
	//};
	
	// Quando uma janela recebe o foco de entrada, ela vira a janela ativa, 
	// por�m se ela tiver uma janela m�e, ent�o a janela m�e ser� a 
	// janela ativa.
	
    if( (void *) window == NULL )
	{
		//Isso e recursivo, pode dar problema.
		//SetFocus(gui->screen);    
		return;
	}else{
		
		//validade e estado da estrutura.
		if( window->used != 1 || window->magic != 1234 ){
			return;
		}
		
		//validade e estado da estrutura.
		if( window->used == 1 && window->magic == 1234 )
		{
			//Salvando id localmente.
			WindowID = (int) window->id; 
			
			//Se a janela j� tem o foco n�o precisa fazer nada.
			if( window->id == window_with_focus ){
				goto setup_wwf;
			}
			
		    //Se a janela � a janela ativa.
			//Ent�o atribuimos o foco e configuramos o procedimento de janela.
			if( window->id == active_window )
			{
	            //set wwf id.
			    window_with_focus = (int) window->id;

			    //set wwf pointer.
			    WindowWithFocus = (void *) window;
				
		        //Procedure.
		        //?? N�o sei se � o ideal.
		        SetProcedure((unsigned long) window->procedure);
				goto setup_wwf;
			};
			
			// Se ela n�o � a janela ativa, tentamos ativar sua janela m�e.
			// Isso se a janela m�o j� n�o for a janela ativa.
            // As janelas filhas nunca s�o janelas ativas. Se uma janela filha 
			// tem o foco de entrada, ent�o sua janela m�e � a ativa. 			
			if( window->id != active_window )
			{
				
			    // Se a janela m�e tem um ponteiro inv�lido. Ent�o ela n�o tem uma 
				// janela m�e, ent�o ativamos a janela filha.
                // ?? #bugbug talvez n�o seja essa ideia certa.			
		        if( (void*) window->parent == NULL ){
			        set_active_window(window);				
		        }else{

					// Testando a validade da janela m�e
				    // Ativar a janela m�e se ela tem um ponteiro v�lido
					// Pois janela filha nunca � a janela ativa, mesmo tendo o foco.
			        if( window->parent->used == 1 && window->parent->magic == 1234 ){
			            set_active_window(window->parent);	
			        };				
				};

                //Obs: Nesse momento a janela ativa est� configurada.
				// a janela ativa � a pr�pria janela ou a sua janela m�e.
                
				
                // J� podemos setar o foco de entrada e configurarmos o 
				// procedimento de janela.				

	            //set wwf id.
			    window_with_focus = (int) window->id;				
		    
			    //set wwf pointer.
			    WindowWithFocus = (void *) window;

		        //Procedure.
		        //?? N�o sei se � o ideal.
		        SetProcedure((unsigned long) window->procedure);

                goto setup_wwf;				
			};
			
			
//
// Nesse momento a janela j� deve estar com o cofo de entrada,
// se n�o estiver � porque falhamos.
//		

    //if( WindowID != window_with_focus )
    //{
	       //window_with_focus = main->id;;      
    //};	
			

//
// Configurando a janela com o foco de entrada.
//
			
setup_wwf:		

			//
			// Temos que posicionar o cursor caso a janela seja um editbox.	
			
			//
			// Se a janela for um editbox, ela precisa ter seu input resetado..
			// para que o procedimento de janela do kernel possa us�-lo.
			// por enquanto, faremos isso para todos os tipos de janelas.
			//
			
			//
			// Reiniciando as margens para input em janela.
			//
			
			//Resetando o input do procedimento de janela.
			
			//
			// #importante:
			// Salvar a configura��o de cursor espec�fica para essa janela.
			// Pois cada janela vai querer o cursor em um lugar.
			//
			
			//
			// #importante 
			// Tentando colocar o cursor dentro dos limites da �rea de cliente
			// no momento em que setamos o foco.
			//
			
			// Usaremos a �rea de cliente caso ela exista,
			// pois tem janela que simplesmente n�o tem, o ponteiro � nulo.
			if( (void*) window->rcClient != NULL )
			{
			    if( window->rcClient->used == 1 && 
				    window->rcClient->magic == 1234 )
			    {
			        g_cursor_left   = (window->rcClient->left/8);
	                g_cursor_top    = (window->rcClient->top/8) +1; //?? Ajuste tempor�rio.   
	                g_cursor_right  = g_cursor_left + (window->rcClient->right/8);
	                g_cursor_bottom = g_cursor_top + (window->rcClient->height/8);					
			    }
				 
				// Nothing. 
				
			}else{
				
			// Configurando o cursor global gerenciado pelo kernel base.
			    g_cursor_left   = (window->left/8);
	            g_cursor_top    = (window->top/8);   
	            g_cursor_right  = g_cursor_left + (window->right/8);
	            g_cursor_bottom = g_cursor_top + (window->height/8);			
			};
			
	
            g_cursor_x = g_cursor_left; 
	        g_cursor_y = g_cursor_top;  

	
	        //configurando o cursor espec�fico da janela com o foco de entrada.
			window->CursorX = g_cursor_x;
			window->CursorY = g_cursor_y;
            window->CursorColor = COLOR_TEXT;
			
			
			//
			// Buffer do controle editbox.
			// Esse buffer pode ser o arquivo usado pelo editbox.
			//
	
	        for( i=0; i<PROMPT_MAX_DEFAULT; i++ )
	        {
		        prompt[i] = (char) '\0';
		        prompt_out[i] = (char) '\0';
		        prompt_err[i] = (char) '\0';
	        };
            prompt_pos = 0;				
		    
			//... 				
		};
		
	};
	
done:	
	//Nothing.
	return;
};


/*
 *************************************************
 * GetFocus: 
 *     Pega o ponteiro para a estrutura da janela 
 * com o foco de entrada.
 */
void *GetFocus()
{
    return (void *) windowList[window_with_focus];	
};



/*
 ***********************************************
 * windowGetForegroundWindow:
 *     Recupera o handle da janela que o usu�rio 
 * est� trabalhando, ou seja, a janela em primeiro plano.
 */
void *windowGetForegroundWindow()
{
    return (void *) windowList[window_with_focus];		
};

/*
 **********************************************
 * windowSetForegroundWindow:
 *     Coloca uma janela em primeiro plano para o 
 * usu�rio trabalhar nela.
 *     @todo: aumentar aprioridade da thread que 
 * configurou a janela de primeiro plano.
 *     +o input do teclado deve vi pra essa janela.
 *     +modifica��es visuais deve ocorrer na janela 
 * que est� em primeiro plano, para 
 * que ela se destaque.
 * retorno: 0=OK  , 1=error.
 */
int 
windowSetForegroundWindow( struct window_d *window )
{
	if( (void *) window == NULL )
	{
		printf("windowSetForegroundWindow: window\n");
		goto fail;
	}else{
		
	    SetFocus(window);
	    set_active_window(window); 
		//...
	};
	
	//@todo: aumentar a prioridade da thread.
done:	
	return (int) 0;
fail:
    return (int) 1;
};





/*
 muda qual sra a janela ativa.
 Obs: Quando mudamos qual ser� a janela ativa
 temos que atualizar qum ser� a janela com o foco de entrada.
 ... e as janes com o foco de entrada devem ficar numa lista.
 .. que provavelmente � a lista de janelas filhas.
void windowSwitchActiveWindow();
void windowSwitchActiveWindow()
{}
*/


/*
 ********************************
 * windowSwitchFocus:
 *     Muda a janela que est� com foco de entrada.
 *     @todo: Selecionar a janela indicada como next 
 * na estrutura.
 *     Em cada momento o foco est� em uma lista de janelas
 * e quando trocamos o foco, percorremos a lista atual.
 * mas a lista muda dependendo do ambeinte gr�fico que 
 * estamos.
 * Muda quando trocamos a janela ativa, muda quando 
 * trocamos o desktop.
 * 
 */
void windowSwitchFocus()
{
	int Max;
	int CurrentID;
	int NextID;

    struct window_d *window;
	struct window_d *next;	
	//...
	
	//Max e Current.
	Max     = (int) windows_count;
	CurrentID = (int) window_with_focus;	//salva
	
	//
	// @todo: 
	// Essa rotina precisa ser refeita. 
	// Seguindo uma lista linkada de janelas.
	//
	
	window = (void*) windowList[window_with_focus];	
	
	if( (void*) window == NULL )
	{
		printf("windowSwitchFocus: window\n");
	    goto fail; 
	}else{
		
	    KillFocus(window);  
		
		//Se a pr�xima janela � v�lida.
		if( (void*) window->next != NULL )
		{
			//Get next.
		    next = (void*) window->next;  
		   	    
			//Current id.	
		    NextID = (int) next->id;     
		   
		    //Se estiver dentro dos limites usaremos a pr�xima.
		    if(NextID > 0 && NextID < Max){
		        window_with_focus = (int) NextID;
	        }else{
			    window_with_focus = (int) CurrentID;	
			}			

		    window = (void*) windowList[window_with_focus];			
            SetFocus(window);
			goto done;			
		}else{
		    window_with_focus = (int) CurrentID;	
		    window = (void*) windowList[window_with_focus];			
            SetFocus(window);
            goto done;  			
		};
		//Fail.
	};
	//Nothing.
done:
    redraw_window(window);
	
    //Debug message:  
	//@todo: Criar mecanismo melhor pra mostrar a janela com o foco.
    //printf("Focus={%d}\n", (int) window_with_focus);
	//refresh_screen();
	
	return;
	
fail:
    return;
};


/*
 *************************************
 * KillFocus:
 *     Uma janela perde o foco.
 */
void KillFocus( struct window_d *window )
{
    //Check.
	if( (void *) window == NULL )
	{
		printf("KillFocus: window\n");
	    goto fail; 
	};
	
	//Focus.
	//window->focus = (int) 0;
    
	// ?? @todo: Quem deve receber o foco nesse caso ??
	// ?? um �ndice antes no zorder ??
	
	if( (void*) gui->main != NULL )
	{
		if( gui->main->used == 1 && 
		    gui->main->magic == 1234 )
		{
	        window_with_focus = (int) gui->main->id;
		};
	}
	//
	// Pra onde vai o foco ??
	//
	
	//set next window
	if( (void*) window->parent != NULL )
	{
		if( window->parent->used == 1 && 
		    window->parent->magic == 1234 )
		{
		    SetFocus(window->parent); 	
		}; 	    
    };	
	
	// Nothing.
	
done:
	return;
fail:
    return;
};


/*
 ******************************************
 * MinimizeWindow:
 *     Minimiza uma janela.
 *     @todo windowMinimize()
 */
void MinimizeWindow(struct window_d *window)
{
	int Status;
	
    if( (void *) window == NULL)
	{
		printf("MinimizeWindow: window\n");
	    goto fail; 
	};
	
	Status = (int) is_window_minimized(window);
    if(Status == 1)
	{
		printf("MinimizeWindow: Status\n");
	    goto fail; 
	};	
	
	//
	//@todo: Redraw ?!
	//
	
done:
    KillFocus(window);
	window->view = (int) VIEW_MINIMIZED;
    return;
fail:
    return;	
};


/*
 **************************************
 * MaximizeWindow:
 *     Maximiza uma janela.
 *     @todo: windowMazimize()
 */
void MaximizeWindow(struct window_d *window)
{
	int Status;
	
    if( (void *) window == NULL)
	{
		printf("MaximizeWindow: window\n");
	    goto fail; 
	};
	
	Status = (int) is_window_maximized(window);
    if(Status == 1)
	{
		printf("MaximizeWindow: Status\n");
	    goto fail; 
	};

    //redimensionar.
	if( gui->main != NULL )
	{
        window->left = gui->main->left;             
        window->top = gui->main->top;                   
	    
		window->width = gui->main->width;             
        window->height = gui->main->height;
	}; 	

	//
	//@todo: Redraw ?!
	//
	
done:
    set_active_window(window);
	SetFocus(window);
	window->view = (int) VIEW_MAXIMIZED;
    return;
fail:
    return;	
};


/*
 *************************************************
 * init_window_manager:
 *     Inicializa o gerenciamento de janelas.
 *     @todo windowmanagerInit()
 */
int init_window_manager()
{
	//
    // Aloca mem�ria para a estrutura do procedimento 
	// de janela da thread atual.
	//
	
	//
	// ## Window procedure struct ##
	//
	
	
	WindowProcedure = (void*) malloc( sizeof( struct window_procedure_d ) );
	
	if( (void*) WindowProcedure == NULL )
	{
	    printf("init_window_manager: WindowProcedure\n");
		die();
	}else{
		
 	    //
	    // Configura a janela ativa. 
	    // Configura a janela com o foco de entrada. 
	    // Se a janela com o foco de entrada for uma 
		// janela filha,ent�o a janela m�e ser� a 
		// janela ativa.
	    //
	
	    WindowProcedure->active_window = (int) 0;
	    WindowProcedure->window_with_focus = (int) 0;
		//...
	};


	//
	// @todo:  
	//     Continua fazendo inicializa��es de 
	// procedimento de janela.
	//
	
done:

#ifdef KERNEL_VERBOSE
    printf("done\n");
#endif

    return (int) 0;
};


/*
 *****************************************
 * init_windows:
 *     Inicializa a lista de janelas.
 *     Inicializa globais relativas � janelas.
 */
int init_windows()
{
		
	//#debug
	// Inicializa a lista de janelas.
	//printf("init_windows:\n");  	
	
	int Offset;
	for( Offset=0; Offset < WINDOW_COUNT_MAX; ++Offset ){
	    windowList[Offset] = (unsigned long) 0;
	}
	
	windows_count = 0;
	
	// Set current.
	set_current_window(NULL);
	
	//
	// ## Client Area ##
	// Inicializando a estrutura do ret�ngulo 
	// da �rea de cliente.
	//
	
	rectClientArea = (void*) malloc( sizeof(struct rect_d) );
    
	if( (void*) rectClientArea == NULL )
	{	
	    printf("init_windows: rectClientArea\n");
		die();
	}else{
	    setClientAreaRect( 0, 0, 0, 0);	
	};
	
	
	//
    // Set fonts. @todo: Criar uma estrutura para 
	// caracter�sticas do char.
	//
		
	// 8x8 
	// 0x000FFA6E;    //ROM.
	g8x8fontAddress  = (unsigned long) BIOSFONT8X8; 
	//g8x16fontAddress = (unsigned long) 0x000FFA6E; 
	//...
	
	//@todo: create SetFontAddress(.)
	gfontAddress = (unsigned long) g8x8fontAddress;
	
	//
	// Char parameters.
	//
	
	//@todo: Create SetCharParam(.,.)
	gcharWidth = (int) 8;
	gcharHeight = (int) 8;	
	
	//...	
	
	//
	// @todo:
	// Pega o video mode passado pelo Boot Loader e 
	// registra na global e na estrutura.
	//
	
	/*
	
	//video mode
	if( kArg1 > 0)
	{
	    printf("init_windows: Configurando modo de video.");
	    SetVideoMode(kArg1);
	};
	
	//LFB
	if( kArg2 != LFB_BASE)
    {
        printf("init_windows: LFB error");
		//@todo hang
    };	
	
	*/
	
	//Inicializando vari�veis.
	current_windowstation = 0;
	current_desktop = 0;
	current_window = 0;
	windows_count = 0;
	window_with_focus = 0;
	current_menu = 0;
    //Continua...		

	
	//inicializando os esquemas de cores.
	//@todo: Isso poderia ter um argumento, selecionado entre o 
	//tipo 1 e 2, humility e pride.
	//ColorSchemeHumility ou ColorSchemePride
	windowSetUpColorScheme(ColorSchemeHumility);
	//windowSetUpColorScheme(ColorSchemePride);	
	
	//input buffer support ??
	//output buffer support ??
	
	
	//inicializar as estruturas de backbuffer e frontbuffer.
	
//
// Backbuffer support. (espelho da mem�ria de video)
//

//BackBufferSupport:
	
	BackBufferInfo = (void*) malloc( sizeof(struct backbufferinfo_d) );
    
	if((void*) BackBufferInfo == NULL)
	{
	    //goto fail;
	
	}else{
	    BackBufferInfo->used = 1;
        BackBufferInfo->magic = 1234;
        //BackBufferInfo->start = ?
        //BackBufferInfo->end = ?
        //BackBufferInfo->size = ?
        //...		
	};		
	

//
// Frontbuffer support. (mem�ria de v�deo)
//
	
//FrontBufferSupport:

	FrontBufferInfo = (void*) malloc( sizeof(struct frontbufferinfo_d) );
    
	if( (void*) FrontBufferInfo == NULL )
	{	
	     //goto fail;	
	}else{
		
		//Algumas informa��es foram enviadas pelo boot loader.
	    FrontBufferInfo->used = 1;
        FrontBufferInfo->magic = 1234;
        //FrontBufferInfo->start = ?
        //FrontBufferInfo->end = ?
        //FrontBufferInfo->size = ?	

        //FrontBufferInfo->width = ?	
        //FrontBufferInfo->height = ?	
        //FrontBufferInfo->bpp = ?			
		
        //... 

        //?? console ??		
	};		

	
	/*
	  test - testando queue para teclado.
	 ************************************
	 */
	 
	//inicializando a fila do sistema usada pelo teclado. 
	//initializeQueue(&myQueue); 
	 
	 
	keyboard_message_head = 0;
    keyboard_message_tail = 0;	
	
    //inicializando fila de teclado.
	int k;
	for( k=0; k<128; k++){
		keybuffer[k] = 0; 
	}
	
	keybuffer_tail = 0;
	keybuffer_head = 0;

	
	//
	// #importante:
	// Nesse momento n�o existem estruturas prontas 
	// para carregar arquivos.
	//
   		
	//
	// Continua ...
	//
	
done:	
    //printf("Done.\n");
	return (int) 0;
fail:
	return (int) 1;
};


//pegando a z-order de uma janela.
int get_zorder( struct window_d *window )
{
    if( (void*) window != NULL ){
		return (int) window->zIndex;
	}		
fail:
	return (int) -1;
};


	//refletindo ??
    //se um argumento for passado teremos que examinar a ordem das janelas filhas.	
	//sendo assim cada estrutura de janela precisa de uma lista de janelas filhas 
	// e a zorder delas ... 
	//
	//se nenhuma janela for passada como argumento 
	// teremos que olhar as janelas filhas da janela principal que � a gui->main ...
	//a janela gui->main pode ser a janela mae de todas as outras ...
	// sendo a janela gui->main a janela principal do processo kernel.
	//o processo explorador de arquivos poder� ser o processo que 
	//seja a m�e de todos os aplicativos de usu�rio ... ent�o a 
	//z order na estrutura da janela desse aplicativo indica a ordem 
	//das janelas principais dos seus processos filhos ...
	//??
	// Uma estrutura de janela pode ter uma vari�vel top_window indicando o id 
	// da janela que est� no topo da z-order da janela.
	//
	
//pegando a o id da janela que est� no topo da lista de uma janela.
struct window_d *getTopWindow(struct window_d *window)
{
	
	if( (void*) window == NULL )
	{
		return ( struct window_d * ) windowList[top_window];
	};
	
	return NULL;
}; 


int get_top_window()
{
	return (int) top_window;
};

//Setando a top window.
void set_top_window( int id )
{
	top_window = (int) id;
};

//fecha a janela ativa.
void closeActiveWindow()
{
    int ID;
	struct window_d *w;
	
	ID = get_active_window();
	
	w = (void*) windowList[ID];
	
	CloseWindow(w);
};


//encontrando um slot livre na z-order global de 
//overlapped windows.
int z_order_get_free_slot()
{
	int response;
	int z; 
	struct window_d *zWindow;

	for( z=0; z < ZORDER_COUNT_MAX; z++ )
	{
	    zWindow = (void*) zorderList[z];
        
		//Obtendo um espa�o vazio.
		//Se for NULL, ent�o n�o tinha um ponteiro no slot.
		if( (void*) zWindow == NULL )
		{
			response = (int) z; 
			
			zorderCounter++;
			if(zorderCounter >= ZORDER_COUNT_MAX){
				printf("z_order_get_free_slot: zorderCounter\n");
				goto fail;
			}
            
			goto done; 				
		};		
		//Nothing
	};
	
fail:
    return (int) -1;
done:
    return (int) response;	
};


//carrega alguns i�cones do sistema.
int windowLoadGramadoIcons()
{
	printf("windowLoadGramadoIcons:\n");
	
	//
	//  ## Icon support ##
	//
	
iconSupport:	
	// Carregando alguns �cones b�sicos usados pelo sistema.
	
	//@todo checar a validade dos ponteiros.
    appIconBuffer = (void*) allocPageFrames(10);
	fileIconBuffer = (void*) allocPageFrames(10);
	folderIconBuffer = (void*) allocPageFrames(10);
	terminalIconBuffer = (void*) allocPageFrames(10);
	
	if( (void*) appIconBuffer == NULL )
	{
		printf("init_windows: appIconBuffer\n");
	    die();	
	}

	if( (void*) fileIconBuffer == NULL )
	{
		printf("init_windows: fileIconBuffer\n");
		die();
	}

	if( (void*) folderIconBuffer == NULL )
	{
		printf("init_windows: folderIconBuffer\n");
		die();
	}

	if( (void*) terminalIconBuffer == NULL )
	{
		printf("init_windows: terminalIconBuffer\n");
		die();
	}
	
	unsigned long fRet;
	
	//@todo: Checar os retornos.
    fRet = (unsigned long) fsLoadFile("APP     BMP", 
	    (unsigned long) appIconBuffer );	
    if( fRet != 0 )
	{
		printf("init_windows: APP.BMP\n");
		die();		
	}		
    
	fRet = (unsigned long) fsLoadFile("FILE    BMP", 
	    (unsigned long) fileIconBuffer );
    if( fRet != 0 )
	{
		printf("init_windows: FILE.BMP\n");
		die();				
	}
	
	fRet = (unsigned long) fsLoadFile("FOLDER  BMP", 
	    (unsigned long) folderIconBuffer );	
    if( fRet != 0 )
	{
		printf("init_windows: FOLDER.BMP\n");
		die();				
	}
	
	fRet = (unsigned long) fsLoadFile("TERMINALBMP", 
	    (unsigned long) terminalIconBuffer );	
    if( fRet != 0 )
	{
		printf("init_windows: TERMINAL.BMP\n");
		die();				
	}	
	
	
	//#debug
	//isso funcionou.
    //bmpDisplayBMP( appIconBuffer, 1, 1 );
	//refresh_rectangle( 1, 1, 16, 16 );
	//die();	
	
    return 0;
};


//
// End.
//

