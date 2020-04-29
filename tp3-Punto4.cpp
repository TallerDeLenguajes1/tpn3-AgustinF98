#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *TiposProductos[] = {"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

typedef struct 
{
    int ProductoID;   // Numerado en ciclo iterativo
    int Cantidad;   // Entre 1 y 10
    char *TipoProducto;    // Algun valor del arreglo TiposProductos
    float PrecioUnitario;   // Entre 10 - 100
}Producto;

typedef struct 
{
    int ClienteID;   // Numerado en el ciclo iterativo
    char *NombreCliente;    // Ingresado por usuario
    int CantidadProductosAPedir;    // Aleatorio entre 1 y 5
    Producto *Productos;    // El tamaño de este arreglo depende de la variable “CantidadProductosAPedir”
}Cliente;

void cargarClientesYProductos(Cliente *pClientes, int cantClientes);
float CalcularPrecio(float precioUnitario, int Cantidad);
void MostrarClientesYProductos(Cliente *Usuarios, int cantClientes);

int main(){
    srand(time(NULL));

    int cantClientes;
    printf("Ingrese la cantidad de clientes (hasta 5 como maximo): ");
    scanf("%d", &cantClientes);
    printf("\n");
    Cliente *pClientes = (Cliente *) malloc(sizeof(Cliente) * cantClientes);

    cargarClientesYProductos(pClientes, cantClientes);
    MostrarClientesYProductos(pClientes, cantClientes);
    
    free(pClientes);

    getchar();
    return 0;
}

void cargarClientesYProductos(Cliente *pClientes, int cantClientes){

    int maxChar = 100;

    //Carga de clientes
    for (int i = 0; i < cantClientes; i++)
    {
        pClientes[i].ClienteID = i + 1;
        
        pClientes[i].NombreCliente = (char *)malloc(sizeof(char) * 100);
        printf("Nombre del cliente %d: ", pClientes[i].ClienteID);
        scanf("%s", pClientes[i].NombreCliente);

        pClientes[i].CantidadProductosAPedir = rand()%5 + 1;

        pClientes[i].Productos = (Producto *) malloc(sizeof(Producto) * pClientes[i].CantidadProductosAPedir);

        //Carga de productos 
        for (int k = 0; k < pClientes[i].CantidadProductosAPedir; k++)
        {
            pClientes[i].Productos[k].ProductoID = k + 1;
            pClientes[i].Productos[k].Cantidad = rand()%9 + 1;
            pClientes[i].Productos[k].TipoProducto = TiposProductos[rand()%4 + 1];
            pClientes[i].Productos[k].PrecioUnitario = rand()%90 + 11;
        }
    }
    printf("\n");
    printf("--------------------------------");
    printf("\n\n");
}

float CalcularPrecio(float precioUnitario, int Cantidad){
    return precioUnitario * Cantidad;
}

void MostrarClientesYProductos(Cliente *Usuarios, int cantClientes){
    float precioFinal = 0;

    for (int j = 0; j < cantClientes; j++)
    {
        printf("ID del cliente: %d\n", Usuarios[j].ClienteID);
        printf("Nombre del cliente: %s\n", Usuarios[j].NombreCliente);
        printf("Cantidad de productos a pedir: %d\n\n\n", Usuarios[j].CantidadProductosAPedir);
        printf("Productos que lleva:\n\n");

        for (int l = 0; l < Usuarios[j].CantidadProductosAPedir; l++)
        {
            printf("ID del producto: %d\n", Usuarios[j].Productos[l].ProductoID);
            printf("Tipo del producto: %s\n", Usuarios[j].Productos[l].TipoProducto);
            printf("Cantidad del producto: %d\n", Usuarios[j].Productos[l].Cantidad);
            printf("Precio unitario: %.2f\n", Usuarios[j].Productos[l].PrecioUnitario);
            printf("\n");
            precioFinal += CalcularPrecio(Usuarios[j].Productos[l].PrecioUnitario, Usuarios[j].Productos[l].Cantidad);
        }
        
        printf("Precio total a pagar: %.2f\n\n", precioFinal);
        printf("--------------------------------");
        printf("\n\n");
        precioFinal = 0;
    }
}