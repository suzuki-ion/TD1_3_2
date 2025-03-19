#include <Common/DrawGrid.h>
#include <Common/CustomNovice.h>
#include <Stage/StageManager.h>

void DrawGrid(Camera &camera) {
    static const unsigned int color = 0x00000040;

    static int gridStartX = -(static_cast<int>(CustomNovice::WinWidth()) / kMapChipSize);
    static int gridEndX = (static_cast<int>(CustomNovice::WinWidth() * 2.0f) / kMapChipSize);

    static int gridStartY = -(static_cast<int>(CustomNovice::WinHeight()) / kMapChipSize);
    static int gridEndY = (static_cast<int>(CustomNovice::WinHeight() * 2.0f) / kMapChipSize);

    for (int i = gridStartX; i <= gridEndX; i++) {
        CustomNovice::DrawLine(
            camera,
            static_cast<float>(i * kMapChipSize),
            -CustomNovice::WinHeight(),
            static_cast<float>(i * kMapChipSize),
            CustomNovice::WinHeight() * 2.0f,
            color
        );
    }
    for (int i = gridStartY; i <= gridEndY; i++) {
        CustomNovice::DrawLine(
            camera,
            -CustomNovice::WinWidth(),
            static_cast<float>(i * kMapChipSize),
            CustomNovice::WinWidth() * 2.0f,
            static_cast<float>(i * kMapChipSize),
            color
        );
    }
}
