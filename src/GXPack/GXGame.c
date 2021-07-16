#import "Game.h"


static inline uint64_t GetTicks() { 
    static struct timeval t = { .tv_sec = 0, .tv_usec = 0 };
    
    gettimeofday(&t, NULL);
    uint64_t ts = t.tv_sec;
    uint64_t us = t.tv_usec;
    return ((ts * 1000000L) + us) * 10;
}


struct __GXGame  
{
	struct __CFObject obj;
    bool mKeys[SCAN_MASK]; // flag per scan code
    bool mIsRunning;
    bool mMouseDown;
    float mMouseX;
    float mMouseY;
    SDL_Window* mWindow;
    CFString mTitle;
    GLuint mWidth;
    GLuint mHeight;
    Float64 mDelta;
    CFType mSubclass;
    GXGameVTable mVtbl;
    int mTicks;
    int mFps;
    bool mIsFixedTimeStep;
    bool mIsRunningSlowly;
    uint64_t mTargetElapsedTime;
    uint64_t mAccumulatedElapsedTime;
    uint64_t mMaxElapsedTime;
    uint64_t mTotalGameTime;
    uint64_t mElapsedGameTime;
    uint64_t mCurrentTime;
    long mPreviousTicks;
    int mUpdateFrameLag;
    bool mShouldExit;
    bool mSuppressDraw;
};

static struct __CFClass class = {
	.name = "GXGame",
	.size = sizeof(struct __GXGame),
	.ctor = GXGameConstructor,
	.dtor = GXGameFinalize,
	.class = CFClass,
    .tostr = GXGameToString
};

CFClass CFArrayClass = &class;

/** Properties: */
Float64 GXGameDelta     (GXGameRef this) { return this->mDelta; }
Boolean GXGameIsRunning (GXGameRef this) { return this->mIsRunning; }
Boolean GXGameMouseDown (GXGameRef this) { return this->mMouseDown; }
Float32 GXGameMouseX    (GXGameRef this) { return this->mMouseX; }
Float32 GXGameMouseY    (GXGameRef this) { return this->mMouseY; }
Int32   GXGameWidth     (GXGameRef this) { return this->mWidth; }
Int32   GXGameHeight    (GXGameRef this) { return this->mHeight; }
SDL_Window* GXGameWindow(GXGameRef this) { return this->mWindow; }
CFString GXGameTitle (GXGameRef this) { return this->mTitle; }


GXGameRef GXGameNew(char* title, int width, int height, CFType subclass, GXGameVTable* vtbl)
{
    return CFNewObject(GXGameClass, title, width, height, subclass, vtbl);
}

GXGameRef GXGameCreate(char* title, int width, int height, CFType subclass, GXGameVTable* vtbl)
{
    return CFCreateObject(GXGameClass, title, width, height, subclass, vtbl);
}


/**
 * Create Game instance
 * 
 * @param Width of screen
 * @param Height of screen,
 * 
 */
 Boolean
 GXGameConstructor(CFType self, va_list args)
 {
	GXGameRef this = self;
	char *title = va_arg(args, char*);
    int width = va_arg(args, int);
    int height = va_arg(args, int);
    CFType subclass = va_arg(args, CFType);
    GXGameVTable* vtbl = va_arg(args, GXGameVTable*);

    this->mVtbl = vtbl; 
    this->mSubclass = subclass;
    this->midth = width;
    this->mHeight = height;
    this->mTitle = CFStringCreate(title);
    this->mIsRunning = false;
    this->mPreviousTicks = 0;
    this->mIsFixedTimeStep = true;
    this->mShouldExit = false;
    this->mSuppressDraw = false;
    this->mMaxElapsedTime = 500 * TicksPerMillisecond;
    this->mTargetElapsedTime = 166667;
    this->mAccumulatedElapsedTime = 0;
    GXGameCreatePlatform(self);
    return  true;
}

void
GXGameCreatePlatform(GXGameRef this) 
{
    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow(CFStringC(self->mTitle),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->mWidth,
        this->mHeight,
        SDL_WINDOW_RESIZABLE | 
        SDL_WINDOW_SHOWN |
        SDL_WINDOW_OPENGL
    );


    SDL_GL_InitContext(self->mWindow);

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        // success = false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetSwapInterval(1);

    GL.Viewport(0, 0, this->mWidth, this->mHeight);
    GL.Enable(GL_CULL_FACE);
    GL.Enable(GL_BLEND);
    GL.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

CFString
GXGameToString(GXGameRef this) 
{ 
    return CFStringCreate("GXGame"); 
}

/**
 * Start
 */
void
GXGameStart(GXGameRef this)
{
    this->mIsRunning = true;
}

/**
 * Stop
 */
void
GXGameStop(GXGameRef this)
{
}

/**
 * Quit
 */
void
GXGameQuit(GXGameRef this)
{
    this->mIsRunning = false;
    [self Stop];
}

void
GXGameInitialize(GXGameRef this) 
{ 
    this->mVtbl->Initialize(this->mSubclass); 
}

void
GXGameLoadContent(GXGameRef this) 
{ 
    this->mVtbl->LoadContent(this->mSubclass); 
}

void
GXGameUpdate(GXGameRef this, Float64 delta) 
{ 
    this->mVtbl->Update(this->mSubclass, this->mDelta); 
}

void
GXGameDraw(GXGameRef this, Float64 delta) 
{ 
    this->mVtbl->Draw(this->mSubclass, this->mDelta); 
}

Boolean
GXGameGetKey(GXGameRef this, int Key) 
{
    return this->mKeys[Key & SCAN_MASK];
}

/**
 * Run
 */
void
GXGameRun(GXGameRef this) 
{

    [self Initialize];
    [self LoadContent];
    [self Start];

    while (this->mIsRunning) {
        [self RunLoop];
    }
}

/**
 * RunLoop
 */
void
GXGameRunLoop(GXGameRef this)
{
    [self HandleEvents];
    [self Tick];
}

/**
 * Handle events
 */
void
GXGameHandleEvents(GXGameRef this)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        
        switch (event.type) {

            case SDL_QUIT:
                this->mIsRunning = false;
                [self Quit];       
                break;

            case SDL_KEYDOWN: 
                this->mKeys[ event.key.keysym.scancode & SCAN_MASK ] = true;
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    [self Quit];       
                    return;     
                }
                break;
            case SDL_KEYUP:   
                this->mKeys[ event.key.keysym.scancode & SCAN_MASK ] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->mMouseDown = true;
                break;
            case SDL_MOUSEBUTTONUP:
                this->mMouseDown = false;
                break;
            case SDL_MOUSEMOTION:
                this->mMouseX = event.motion.x;
                this->mMouseY = event.motion.y;
                break;


            default: break;
        }
    }
}

/**
 * Tick
 */
void
GXGameTick(GXGameRef this)
{

    while (true)
    {
        // Advance the accumulated elapsed time.
        long currentTicks = GetTicks() - this->mCurrentTime;
        this->mAccumulatedElapsedTime = this->mAccumulatedElapsedTime + currentTicks - this->mPreviousTicks;
        this->mPreviousTicks = (long)currentTicks;

        // If we're in the fixed timestep mode and not enough time has elapsed
        // to perform an update we sleep off the the remaining time to save battery
        // life and/or release CPU time to other threads and processes.
        if (this->mIsFixedTimeStep && this->mAccumulatedElapsedTime < this->mTargetElapsedTime)
        {
            int sleepTime = (int)((this->mTargetElapsedTime - this->mAccumulatedElapsedTime) * MillisecondsPerTick );
            if (sleepTime < 1) break;
            // NOTE: While sleep can be inaccurate in general it is 
            // accurate enough for frame limiting purposes if some
            // fluctuation is an acceptable result.
            // SDL_Delay(sleepTime);
            usleep(sleepTime*1000);
            // goto RetryTick;
        }
        else break;
    }
    // Do not allow any update to take longer than our maximum.
    if (this->mAccumulatedElapsedTime > this->mMaxElapsedTime)
        this->mAccumulatedElapsedTime = this->mMaxElapsedTime;

    if (this->mIsFixedTimeStep)
    {
        this->mElapsedGameTime = this->mTargetElapsedTime;
        int stepCount = 0;

        // Perform as many full fixed length time steps as we can.
        while (this->mAccumulatedElapsedTime >= this->mTargetElapsedTime && !this->mShouldExit)
        {
            this->mTotalGameTime += this->mTargetElapsedTime;
            this->mAccumulatedElapsedTime -= this->mTargetElapsedTime;
            ++stepCount;
            this->mDelta = (double)this->mElapsedGameTime * SecondsPerTick;
            [self Update:this->mDelta];
            // DoUpdate(&mGameTime);
        }
        //Every update after the first accumulates lag
        this->mUpdateFrameLag += Max(0, stepCount - 1);
        //If we think we are running slowly, wait until the lag clears before resetting it
        if (this->mIsRunningSlowly)
        {
            if (this->mUpdateFrameLag == 0)
            
                this->mIsRunningSlowly = false;
        }
        else if (this->mUpdateFrameLag >= 5)
        {
            //If we lag more than 5 frames, start thinking we are running slowly
            this->mIsRunningSlowly = true;
        }
        //Every time we just do one update and one draw, then we are not running slowly, so decrease the lag
        if (stepCount == 1 && this->mUpdateFrameLag > 0)
            this->mUpdateFrameLag--;

        // Draw needs to know the total elapsed time
        // that occured for the fixed length updates.
        this->mElapsedGameTime = this->mTargetElapsedTime * stepCount;

    }
    else
    {
        // Perform a single variable length update.
        this->mElapsedGameTime = this->mAccumulatedElapsedTime;
        this->mTotalGameTime += this->mAccumulatedElapsedTime;
        this->mAccumulatedElapsedTime = 0; 

        // Update();
        [self Update:this->mDelta];
    }

    // Draw unless the update suppressed it.
    if (this->mSuppressDraw)
        this->mSuppressDraw = false;
    else
    {
        // Draw();
        [self Draw:this->mDelta];
    }

    if (this->mShouldExit) this->mIsRunning = false;
        // Platform.Exit();

}


/**
 * Release game resources
 */
void
GXGameFinalyze(GXGameRef this)
{
    SDL_GL_DeleteContext(GL.context);  
    SDL_DestroyWindow(this->mWindow);
    SDL_Quit();
}

