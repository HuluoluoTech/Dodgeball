# Dodgeball

### 热身
#### UE 坐标系 - 左手坐标系
RED (X) - GREEN(Y) - BLUE(Z)  

#### Tick(DeltaTime)
DeltaTime -> Indicates the amount of time that passed since the last frame was rendered.
60FPS VS.30 FPS
So, , It will cause two players palying the game with different frame rates to have the same result.

#### DefaultInput.ini
Input Settings -> Action Mappings ...  

#### FRotator 参数
```c
// Roll -> X
// Pitch -> Y
// Yaw -> Z
const FRotator Rotation(Pitch, Yaw, Roll)
const FRotator Rotation(Y, Z, X)
```

#### 鼠标控制Player: 
##### 上下、左右
```c
// Pitch -> Y 轴旋转
PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

// Yaw -> Z 轴旋转
PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
```

##### 前后
```c
PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHuluoluoCharacter::MoveForward);
PlayerInputComponent->BindAxis("Move Right / Left", this, &AHuluoluoCharacter::MoveRight);
```

#### 继承关系
AActor -> APawn -> ACharacter
修改Character属性，blueprint会覆盖掉代码构造方法中的设置。

#### 调试
```c
#include "DrawDebugLine.h"
```

#### 工具库 Kismet
```c
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
```

#### Collision
is A point at which two objects come into contact with each other.

1. Meshes 
1.1 Static Mesh
1.2 Skeletal Mesh
2. Shape objects
2.1 Box Component
2.2 Sphere Component
2.3 Capsule Component

##### Collision Events
Ignore / Overlap / Block ; 优先级递减
Ignore & Overlap = Ignore
Overlap & Block = Overlap

SimulationGeneratesHitEvents = true : OnHit
GenerateOverlapEvents = true; OnBeginOverlap / OnEndOverlap

##### UProjectileMovementComponent
updates the position of another component during its tick.

##### 自定义 Preset
```c
Project Settings -> Engine -> Collision
```

#### TSubclassOf , C++ 和 Blueprint 交互
```c
TSubclassOf<class ADodgeballProjectile> DodgeballClass;
```
a way to reference a Blueprint class in C++

或者 
```c
ADodgeballProjectile::StaticClass()
```

获取 Class

#### SpawnActor
- SpawnActor
- SpawnActorDeferred , FinishSpawning

### Timer
```c
FTimerHandle ThrowTimerHandle;
GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&AEnamyCharacter::ThrowDodgeball,
				ThrowingInterval,
				true,
				ThrowingDelay);
GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
```

### UMG - Unreal Motion Graphics
* Canvas Panel
* Anchor

#### Update `x.build.cs`
`PublicDependencyModuleNames...(UMG, Slate, SlateCore)`


### 工具方法
```c
* GetWorld()
* GetOwner()
* GetController()
* ADodgeballProjectile::StaticClass()
* SetLifeSpan(5.0f);
* UKismetSystemLibrary::QuitGame
* UGameplayStatics::OpenLevel
* RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
* GetOwner()->Implements<UHealthInterface>()
* Cast<ADodgeballCharacter>(GetOwner());
* UE_LOG(LogTemp, Warning, TEXT("ShowRestartWidget"));
* SetInputMode（）
* Destroy()
* UGameplayStatics::GetCurrentLevelName

```

