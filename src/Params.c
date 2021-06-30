#include "Params.h"

static struct option longopts[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'V'},
    {"scrot", no_argument, NULL, 's'},
    {"calendar", required_argument, NULL, 'c'},
    {"pin", required_argument, NULL, 'p'},
    {"verbosity", required_argument, NULL, 'v'},
    {"font", required_argument, NULL, 'f'},
    {"theme", required_argument, NULL, 't'},
    {"tz", required_argument, NULL, 'z'}
};

Params* Params_New()
{
    Params* this = (Params*)malloc(sizeof(Params));
    return this;
}

void Params_Init(Params* this, int argc, char **argv) 
{
    int longindex = -1;
    int opt = 0;

    while ((opt = getopt_long(argc, argv, "oshVt:v:f:a:c:p:", longopts, &longindex))!= -1) {
        switch (opt) {
        case 's':
            this->scrot = true;
            break;
        case 'h':
            this->help = true;
            break;
        case 'V':
            this->version = true;
            break;
        case 'c':
            if (this->calendar != NULL) {
                free(this->calendar);
            }
            this->calendar = strdup(optarg);
            break;
        case 'p':
            if (this->pin != NULL) {
                free(this->pin);
            }
            this->pin = strdup(optarg);
            break;
        case 'f':
            if (this->font_name != NULL) {
                free(this->font_name);
            }
            this->font_name = strdup(optarg);
            break;
        case 't':
            if (this->theme_name != NULL) {
                free(this->theme_name);
            }
            this->theme_name = strdup(optarg);
            break;
        case 'v':
            this->verbosity = atoi(optarg);
            break;
        case 'z':
            this->tz = atoi(optarg);
            break;
        default:
            break;
        }
    }

    if (this->verbosity > 0) {
        printf("font: \"%s\"\n", this->font_name);
        printf("verbosity: %d\n", this->verbosity);
    }

    if (this->version) {
        puts("\ncatlock v0.1.0, © 2020 Dark Overlord of Data");
        puts("inspired by metalock © 2012 Timothy Beyer");
        exit(0);
    }

    if (this->help) {
        puts("Usage: catlock [option]\n");

        puts("-h / --help               help (this)");
        puts("-V / --version            version information");
        puts("-s / --scrot              take screen pics");
        puts("-c / --calendar           calendar app, such as \"orage\"");
        puts("-v n / --verbosity n      verbosity level (default: 0)");
        puts("-f name / --font name     X11 font name");
        puts("-t name / --theme name    theme name (default: badabing)");

        puts("\nhttps://github.com/darkoverlordofdata/kitty-cat-lock" );
        exit(0);
    }


}

void Params_Dispose(Params* this)
{
    free(this->calendar);
    free(this->font_name);
    free(this->theme_name);
    free(this->calendar);
    free(this->pin);
}

void Params_Print(Params* this)
{
    printf("tz adjustment %d\n", this->tz);
    printf("verbosity %d\n", this->verbosity);
    printf("calendar %s\n", this->calendar);
    printf("theme_name %s\n", this->theme_name);
    printf("font_name %s\n", this->font_name);
    printf("pin %s\n", this->pin);
    printf("scrot %x\n", this->scrot);
    printf("help %x\n", this->help);
    printf("version %x\n", this->version);
}