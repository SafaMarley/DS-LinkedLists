#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PRODUCTS {
	int pID;
	char name[50];
	char category[20];
	int price;
	struct PRODUCTS* nextProduct;
};

struct BASKETS {
	int cID;
	int bID;
	int totalAmount;
	struct PRODUCTS* productList;
	struct BASKETS* nextBasket;
};

struct CUSTOMERS {
	int cID;
	char name[40];
	char surname[40];
	struct BASKETS* basketList;
	struct CUSTOMERS* nextCustomer;
};

typedef struct PRODUCTS Products;
typedef struct BASKETS Baskets;
typedef struct CUSTOMERS Customers;



void printCustomers(Customers* headCustomer){/*This function
    does not take address of headers as parameters because it should not change these directions.
    */

    printf("\nID___Name________Surname\n");
    while (headCustomer != NULL) {/*For printing customers as name ordered the name, surname and ID
        have to pointed by the name_head, because in this loop -as I mentioned just before- prints
        the customers as "name" ordered. */
        printf("%-5d%-12s%s\n", headCustomer->cID, headCustomer->name, headCustomer->surname);
        headCustomer = headCustomer->nextCustomer; /*This line changes the nHeader pointer to the next node(customers)
        to iterate.*/
    }
}

void printProducts(Products* headProduct){/*This function
    does not take address of headers as parameters because it should not change these directions.
    */

    printf("\nID___Name________Category_______Price\n");
    while (headProduct != NULL) {/*For printing customers as name ordered the name, surname and ID
        have to pointed by the name_head, because in this loop -as I mentioned just before- prints
        the customers as "name" ordered. */
        printf("%-5d%-15s%-15s%d\n", headProduct->pID, headProduct->name, headProduct->category, headProduct->price);
        headProduct = headProduct->nextProduct; /*This line changes the nHeader pointer to the next node(customers)
        to iterate.*/
    }
}

void printALLINFO(Customers* headCustomer){/*This function
    does not take address of headers as parameters because it should not change these directions.
    */
    printf("\nID___Name________Surname\n");
    while (headCustomer != NULL) {/*For printing customers as name ordered the name, surname and ID
        have to pointed by the name_head, because in this loop -as I mentioned just before- prints
        the customers as "name" ordered. */
        Baskets * tempBasketList = headCustomer->basketList;
        printf("%-5d%-12s%s\n", headCustomer->cID, headCustomer->name, headCustomer->surname);

        while(tempBasketList != NULL){
            Products *tempProductList = tempBasketList->productList;
            printf("    basketId: %d    total Price of Basket: %d\n", tempBasketList->bID, tempBasketList->totalAmount);

            while(tempProductList != NULL){
                printf("        ProductName: %s\n", tempProductList->name);

                 tempProductList = tempProductList->nextProduct;
            }

            tempBasketList = tempBasketList->nextBasket;
        }
        headCustomer = headCustomer->nextCustomer; /*This line changes the nHeader pointer to the next node(customers)
        to iterate.*/
    }
}

void printSpecificProductBuyers(int pID4, Customers * headCustomer){

    printf("\nID___Name________Surname\n");
    while (headCustomer != NULL) {/*For printing customers as name ordered the name, surname and ID
        have to pointed by the name_head, because in this loop -as I mentioned just before- prints
        the customers as "name" ordered. */
        Baskets * tempBasketList = headCustomer->basketList;

        while(tempBasketList != NULL){
            Products *tempProductList = tempBasketList->productList;

            while(tempProductList != NULL){
                 if(tempProductList->pID == pID4){
                    printf("%-5d%-12s%s\n", headCustomer->cID, headCustomer->name, headCustomer->surname);
                 }

                 tempProductList = tempProductList->nextProduct;
            }

            tempBasketList = tempBasketList->nextBasket;
        }
        headCustomer = headCustomer->nextCustomer; /*This line changes the nHeader pointer to the next node(customers)
        to iterate.*/
    }

}

void printTotalAmounts(Customers *headCustomer){
    printf("\nID___Name________Surname_____Total Amount\n");
    while(headCustomer != NULL){
        Baskets * tempBasketList = headCustomer->basketList;
        int totalAmount = 0;

        while(tempBasketList != NULL){
            totalAmount += tempBasketList->totalAmount;
            tempBasketList = tempBasketList->nextBasket;
        }
        if(totalAmount != 0){
            printf("%-5d%-12s%-12s%d\n", headCustomer->cID, headCustomer->name, headCustomer->surname, totalAmount);
        }else{
            printf("%-5d%-12s%-12sNo Shopping\n", headCustomer->cID, headCustomer->name, headCustomer->surname);

        }

        headCustomer = headCustomer->nextCustomer;
    }

}


int isProductExist(Products *headProductPtr, int pID){
    ///ITS SO IMPORTANT TO GET headProductPtr NOT crntCustomerPtr
    ///Because otherwise we are unintentionally changing the
    ///product pointers. So function affects can be seen on
    ///outside the function.

    Products * tempProductPtr = headProductPtr;

    while(tempProductPtr != NULL){
        if(tempProductPtr->pID == pID){
            return 1;
        }
        tempProductPtr = tempProductPtr->nextProduct;
    }
    return 0;
}

int isBasketExist(Baskets *headBasketPtr, int bID){
    ///ITS SO IMPORTANT TO GET headBasketPtr NOT crntCustomerPtr
    ///Because otherwise we are unintentionally changing the
    ///basket pointers. So function affects can be seen on
    ///outside the function.

    Baskets * tempBasketPtr = headBasketPtr;

    while(tempBasketPtr != NULL){
        if(tempBasketPtr->bID == bID){
            return 1;
        }
        tempBasketPtr = tempBasketPtr->nextBasket;
    }
    return 0;
}

int isCustomerIdExist(Customers * headCustomerPtr, int cID){

    Customers * tempCustomerPtr = headCustomerPtr;

    while(tempCustomerPtr != NULL){
        if(tempCustomerPtr->cID == cID){
            return 1;
        }
        tempCustomerPtr = tempCustomerPtr->nextCustomer;
    }
    return 0;
}

int isCustomerNameSurnameExist(Customers * headCustomerPtr, char name[40], char surname[40]){

    Customers * tempCustomerPtr = headCustomerPtr;

	while(tempCustomerPtr != NULL){
        //printf("\nn: %s tn: %s \n", name, tempCustomerPtr->name);
        //printf("s: %s ts: %s ", surname, tempCustomerPtr->surname);
        //printf("\n\nname compare: %d \nsurname compare: %d\n\n\n", strcmp(name, tempCustomerPtr->name), strcmp(surname, tempCustomerPtr->surname));
        if(strcmp(name, tempCustomerPtr->name) == 0 && strcmp(surname, tempCustomerPtr->surname) == 0){
            //printf("        name -> %s ||| temp name-> %s \n", name, tempCustomerPtr->name);
            //printf("        SURname -> %s ||| temp SURname-> %s \n", surname, tempCustomerPtr->surname);

            return 1;
        }
		tempCustomerPtr = tempCustomerPtr->nextCustomer;

	}
	return 0;
}



void addProduct(int pID, char name[41], char category[41], int price, Products **headProduct) {

	if(isProductExist(*headProduct, pID) == 0){
        Products* newProduct = (Products*)malloc(sizeof(Products));
        if(newProduct != NULL){
            newProduct->pID = pID;
            strcpy(newProduct->name, name);
            strcpy(newProduct->category, category);
            newProduct->price = price;
            newProduct->nextProduct = NULL;

            //FOR ARRANGE PRODUCTS POINTERS:
            Products* prvsPtr = NULL;//
            Products* crntPtr = *headProduct;

            //This loop finds the correct location in the Products list.
            while (crntPtr != NULL && strcmp(name, crntPtr->name) > 0){
                prvsPtr = crntPtr;
                crntPtr = crntPtr->nextProduct;
            }

            if (prvsPtr == NULL){//Insert new node at the beginning of the Products list.
                newProduct->nextProduct = *headProduct;//*headProduct is NULL at this point.
                *headProduct = newProduct;//*headProduct shows the first Products in the list.

            }else{//Insert new node between previous and current pointer.
                prvsPtr->nextProduct = newProduct;
                newProduct->nextProduct = crntPtr;
            }

        }else{
            printf(">ERROR< Memmory couldn't allocated for PRODUCT.\n");
        }

	}else{
        printf(">ERROR< Given PRODUCT already exists.\n");
	}

}

void addProduct2CustomerBasket(int pID, int bID, int cID, Customers *headCustomer, Products * headProduct){

    Products * crntProductPtr = headProduct;

    Customers * crntCustomerPtr = headCustomer;

    //printf("\n\n--------------Inside addProduct2CustomerBasket--------------\n");

    if(isProductExist(headProduct, pID) == 1 && isCustomerIdExist(headCustomer, cID) == 1){

        while (crntCustomerPtr->cID != cID){// For finding the right customer
            crntCustomerPtr = crntCustomerPtr->nextCustomer;
            //printf("cIDs: %d - %d\n", crntCustomerPtr->cID, cID);
        }

        if(isBasketExist(crntCustomerPtr->basketList, bID) || bID == -1){
            Baskets * crntBasketPtr = crntCustomerPtr->basketList;

            /*Below if-else statement gives as a flexibility to
            write the basketID's in the basket.txt file randomly.
            To illustrate, if given text is like:
            nameID  basketID productID
            1        2        2
            1        1        5
            rather than:
            1        1        2
            1        2        6
            Code still works. Also, that means we can put products
            into whatever basket we want, it doesn't depend on how much
            basket we have.*/

            if(bID == -1){

                while(crntBasketPtr->nextBasket != NULL){
                    crntBasketPtr = crntBasketPtr->nextBasket;
                }

            }else{
                while(crntBasketPtr->bID != bID){// For finding right basket
                    crntBasketPtr = crntBasketPtr->nextBasket;
                    //printf("bIDs: %d - %d\n", crntProductPtr->pID, pID);
                }
            }

            while (crntProductPtr->pID != pID){// For finding the right product
                crntProductPtr = crntProductPtr->nextProduct;
                //printf("pIDs: %d - %d\n", crntProductPtr->pID, pID);
            }

            //Products* prvsPtr = NULL;//
            //Products* crntPtr = crntBasketPtr->productList;

            int ProductID = crntProductPtr->pID;
            char ProductName[49];
            char ProductCategory[19];
            int ProductPrice = crntProductPtr->price;

            strcpy(ProductName, crntProductPtr->name);
            strcpy(ProductCategory, crntProductPtr->category);

            addProduct(ProductID, ProductName, ProductCategory, ProductPrice, &crntBasketPtr->productList);
            crntBasketPtr->totalAmount += ProductPrice;
            /*
            //This loop finds the correct location in the product list of basket of customer.
            while (crntPtr != NULL && pID > crntPtr->pID ){
                prvsPtr = crntPtr;
                crntPtr = crntPtr->nextProduct;
            }

            if (prvsPtr == NULL){//Insert new node at the beginning of the name list.
                //addProduct(pID, crntProductPtr->name, crntProductPtr->category, crntProductPtr->price, );


                crntProductPtr->nextProduct = *namesPtr;
                *namesPtr = crntProductPtr;

            }else{//Insert new node between previous and current pointer.
                //addProduct();

                prvsPtr->nextProduct = crntProductPtr;
                crntProductPtr->nextProduct = crntPtr;
            }*/

            //strcpy(newProduct->name, name);
            //strcpy(newProduct->category, category);

        }else{
            printf(">ERROR< There are no such BASKET.\n");
        }
    }else{
        printf(">ERROR< There are no such PRODUCT or CUSTOMER.\n");
    }

}

void addBasket(int cID, int bID, Customers **headCustomer){
    //printf("\n\n-----------------Inside AddBasket: ----------------\n");
    Customers* crntCustomerPtr = *headCustomer;

    //This loop finds the correct customer.
    while (crntCustomerPtr->cID != cID){
        crntCustomerPtr = crntCustomerPtr->nextCustomer;
        //printf("%d - %d\n", crntCustomerPtr->cID, cID);
    }

    if (crntCustomerPtr->basketList == NULL){ //This is for creating the first basket
        //printf("inside IF\n");
        Baskets * newBasket = (Baskets*)malloc(sizeof(Baskets));
        if (newBasket != NULL){
            newBasket->bID = bID;
            newBasket->cID = cID;
            newBasket->totalAmount = 0;
            newBasket->productList = NULL;


            if(bID == -1){ //To call it from main menu.
                newBasket->bID = 1;
            }

            newBasket->nextBasket = crntCustomerPtr->basketList;
            crntCustomerPtr->basketList = newBasket;

        }else{
            printf(">ERROR< Memmory couldn't allocated for BASKET.\n");
        }

    }else{ //This is for creating rest of the baskets.


        if (isBasketExist(crntCustomerPtr->basketList, bID) == 0){
            //printf("bIDs: %d - %d\n", crntCustomerPtr->basketList->bID, bID);
            Baskets * newBasket = (Baskets*)malloc(sizeof(Baskets));

            if(newBasket != NULL){
                newBasket->bID = bID;
                newBasket->cID = cID;
                newBasket->totalAmount = 0;
                newBasket->nextBasket = NULL;
                newBasket->productList = NULL;


                //FOR ARRANGE BASKET POINTERS:
                Baskets* prvsBasketPtr = NULL;//
                Baskets* crntBasketPtr = crntCustomerPtr->basketList;

                //printf("11111111111\n");
                while (crntBasketPtr != NULL){ //&& strcmp(name, crntPtr->name) > 0
                    prvsBasketPtr = crntBasketPtr;
                    crntBasketPtr = crntBasketPtr->nextBasket;
                }
                //printf("2222222222\n");
                if(bID == -1){
                    int r = prvsBasketPtr->bID + 1;
                    newBasket->bID = r;
                }

                prvsBasketPtr->nextBasket = newBasket;
                newBasket->nextBasket = crntBasketPtr;

                //printf("3333333333333\n");

            }else{
                printf(">ERROR< Memmory couldn't allocated for BASKET.\n");
            }
        }else{
            //printf("basket id exists already.\n");

        }
        //printf("bIDs: %d - %d\n", crntCustomerPtr->basketList->bID, bID);



    }



    //printf("%d - %d\n", crntCustomerPtr->cID, bID);

}

void addCustomer(int cID, char name[40], char surname[40], Customers **headCustomer) {

	Customers* newCustomer = (Customers*)malloc(sizeof(Customers));

    if(newCustomer != NULL){
        newCustomer->cID = cID;
        strcpy(newCustomer->name, name);
        strcpy(newCustomer->surname, surname);
        newCustomer->nextCustomer = NULL;
        newCustomer->basketList = NULL;

        //FOR ARRANGE CUSTOMER POINTERS:
        Customers* prvsPtr = NULL;//
        Customers* crntPtr = *headCustomer;

        //This loop finds the correct location in the customer list.
        while (crntPtr != NULL){
            prvsPtr = crntPtr;
            crntPtr = crntPtr->nextCustomer;
        }

        if(cID == -1){
            int u = prvsPtr->cID + 1;
            newCustomer->cID = u;
        }

        if (prvsPtr == NULL){//Insert new node at the beginning of the customer list.
            newCustomer->nextCustomer = *headCustomer;//*headCustomer is NULL at this point.
            *headCustomer = newCustomer;//*headCustomer shows the first customer in the list.

        }else{//Insert new node between previous and current pointer.
            prvsPtr->nextCustomer = newCustomer;
            newCustomer->nextCustomer = crntPtr;
        }

    }else{
        printf("Memmory couldn't allocated for CUSTOMER.");
    }
}

void removeCustomer(char name[40], char surname[40], Customers **headCustomer){

    Customers * prvsCustomer = NULL;
    Customers * crntCustomer = *headCustomer;

    while(strcmp(crntCustomer->name, name) != 0 && strcmp(crntCustomer->surname, surname) != 0){
        prvsCustomer = crntCustomer;
        crntCustomer = crntCustomer->nextCustomer;
    }

    Customers * tempPtr = crntCustomer;

    if (prvsCustomer == NULL){
        *headCustomer = (*headCustomer)->nextCustomer;

    }else{
        prvsCustomer->nextCustomer = crntCustomer->nextCustomer;
    }

    free(tempPtr);

}


int main(int argc, char *argv[]) {

    // INITIALIZING HEADS OF THE LINKED LIST
	Customers *headCustomer;
	headCustomer = NULL;

	Products *headProduct;
	headProduct = NULL;

	// TEMPORARY VARIABLES WILL GET THE READEN DATA ON FILES
	int customerID;
	char customerName[40];
	char customerSurname[40];

	int productID;
	char productName[41];
	char productCategory[41];
	int productPrice;

	int basketID;
	int bcustomerID;
	int bproductID;

	FILE *cFile, *pFile, *bFile;
	cFile = fopen("Customer.txt","r");
	pFile = fopen("Product.txt", "r");
	bFile = fopen("Basket.txt", "r");
	//printf("headc ID: %d", headCustomer->cID); //This gives an Segmentation error.



    for(fscanf(cFile,"%d %s %s", &customerID, customerName, customerSurname);
    !feof(cFile); fscanf(cFile,"%d %s %s", &customerID , customerName, customerSurname)){

        addCustomer(customerID, customerName, customerSurname, &headCustomer);
    }
    addCustomer(customerID, customerName, customerSurname, &headCustomer);

    fclose(cFile);
    //printCustomers(headCustomer);

    for(fscanf(pFile,"%d %s %s %d", &productID, productName, productCategory, &productPrice);
    !feof(pFile); fscanf(pFile,"%d %s %s %d", &productID, productName, productCategory, &productPrice)){

        addProduct(productID, productName, productCategory, productPrice, &headProduct);
    }
    addProduct(productID, productName, productCategory, productPrice, &headProduct);

    fclose(pFile);
    //printProducts(headProduct);

    for(fscanf(bFile,"%d %d %d", &bcustomerID, &basketID, &bproductID);
    !feof(bFile); fscanf(bFile,"%d %d %d", &bcustomerID, &basketID, &bproductID)){

        addBasket(bcustomerID, basketID, &headCustomer);
        addProduct2CustomerBasket(bproductID, basketID, bcustomerID, headCustomer, headProduct);
    }
    addBasket(bcustomerID, basketID, &headCustomer);
    addProduct2CustomerBasket(bproductID, basketID, bcustomerID, headCustomer, headProduct);
    fclose(bFile);

    int choice = 0;

    printf("\n*** * *  * WELCOME TO THE E-COMMERCE SYSTEM *  * * ***  \n\n");
    while(choice != 6){
        printf("\n1 - Add Customer\n2 - Add Basket \n3 - Remove Customer\n4 - List The Customers Who Bought a"
               " Specific Product\n5 - List The Total Amounts of Each Customer\n6 - EXIT\n\nChoice: ");

        scanf("%d", &choice);
        printf("\n");
        char cName1[40];
        char cSurname1[40];
        int cID2;
        int pID2;
        char cName3[40];
        char cSurname3[40];
        int pID4;

        switch(choice){
        case 1:
            printCustomers(headCustomer);
            printf("Enter a name and surname.\nName: ");
            scanf("%s", cName1);
            printf("Surname: ");
            scanf("%s", cSurname1);

            if(!isCustomerNameSurnameExist(headCustomer, cName1, cSurname1)){//cID is -1 to make function
                addCustomer(-1, cName1, cSurname1, &headCustomer);          //automatically increment 1
                printCustomers(headCustomer);                            //of the last customers ID.

            }else{
                printf(">ERROR< Given NAME-SURNAME is already exists.\n");
            }
            break;

        case 2:
            printCustomers(headCustomer);
            printf("Enter the ID of the name and product.\nName ID: ");
            scanf("%d", &cID2);
            while (isCustomerIdExist(headCustomer, cID2) == 0){
                printf("There is no such name ID, enter again.\nName ID: ");
                scanf("%d", &cID2);
            }
            printProducts(headProduct);
            printf("Product ID (-1 to exit): ");
            scanf("%d", &pID2);

            if(pID2 != -1){
                addBasket(cID2, -1, &headCustomer);
            }
            while(pID2 != -1){
                addProduct2CustomerBasket(pID2, -1, cID2, headCustomer, headProduct);
                printf("Product ID (-1 to exit): ");
                scanf("%d", &pID2);
            }

            printALLINFO(headCustomer);

            break;

        case 3:
            printCustomers(headCustomer);
            printf("Enter the name you want to delete: ");
            scanf("%s", cName3);
            printf("Enter the surname of %s you want to delete: ", cName3);
            scanf("%s", cSurname3);

			if(isCustomerNameSurnameExist(headCustomer, cName3, cSurname3) == 1){
                //printf("555555555555555555555555\n");
                removeCustomer(cName3, cSurname3, &headCustomer);
                printCustomers(headCustomer);
			}else{
                printf("There is no such customer.\n");
			}
            break;

        case 4:
            printProducts(headProduct);
            printf("Enter the product ID\n");
            printf("Product ID: ");
            scanf("%d", &pID4);
            if(isProductExist(headProduct, pID4) == 1){
                printSpecificProductBuyers(pID4, headCustomer);
            }else{
                printf("There is no such product ID\n");
            }
            break;

        case 5:
            printTotalAmounts(headCustomer);

            break;

        default:
            printf("IT IS HARD TO SAY GOOD-BYE\n");
        }
    }

    //printALLINFO(headCustomer);
	return 0;
}

