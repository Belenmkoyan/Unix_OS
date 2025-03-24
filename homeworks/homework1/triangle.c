int main() {

    float height;
    float base;
    float area;
    
    do{
        printf("Enter the height of the triangle: ");
        scanf("%f", &height);

    } while (height <= 0);

    do{
        printf("Enter the base of the triangle: ");
        scanf("%f", &base);
    } while (base <= 0);

    area = 0.5 * height * base;
    printf("The area of the triangle is %.2f\n", area);

    return 0;
}
