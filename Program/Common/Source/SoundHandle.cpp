#include <Novice.h>
#include <Common/SoundHandle.h>

void SoundHandle::Load() {
    for (int i = 0; i < SOUNDS; i++) {
        playHandle_[i] = -1;
    }

    sounds_[SOUND_NONE].id = -1;
    sounds_[SOUND_NONE].volume = 0.0f;
    sounds_[SOUND_NONE].isLoop = false;

    /// 
    /// ↓ここから音声設定
    /// 

    sounds_[BGM_TITLE].id = Novice::LoadAudio("./Resources/Sounds/BGM/title.mp3");
    sounds_[BGM_TITLE].volume = 1.0f;
    sounds_[BGM_TITLE].isLoop = true;

    sounds_[BGM_STAGE_SELECT].id = Novice::LoadAudio("./Resources/Sounds/BGM/stage_select.mp3");
    sounds_[BGM_STAGE_SELECT].volume = 1.0f;
    sounds_[BGM_STAGE_SELECT].isLoop = true;

    sounds_[BGM_GAME].id = Novice::LoadAudio("./Resources/Sounds/BGM/game.mp3");
    sounds_[BGM_GAME].volume = 1.0f;
    sounds_[BGM_GAME].isLoop = true;

    sounds_[SE_SELECT].id = Novice::LoadAudio("./Resources/Sounds/SE/select.mp3");
    sounds_[SE_SELECT].volume = 1.0f;
    sounds_[SE_SELECT].isLoop = false;

    sounds_[SE_DECIDE].id = Novice::LoadAudio("./Resources/Sounds/SE/decide.mp3");
    sounds_[SE_DECIDE].volume = 1.0f;
    sounds_[SE_DECIDE].isLoop = false;

    sounds_[SE_STOP].id = Novice::LoadAudio("./Resources/Sounds/SE/stop.mp3");
    sounds_[SE_STOP].volume = 1.0f;
    sounds_[SE_STOP].isLoop = false;

    sounds_[SE_START].id = Novice::LoadAudio("./Resources/Sounds/SE/start.mp3");
    sounds_[SE_START].volume = 1.0f;
    sounds_[SE_START].isLoop = false;

    sounds_[SE_ROTATE].id = Novice::LoadAudio("./Resources/Sounds/SE/rotate.mp3");
    sounds_[SE_ROTATE].volume = 1.0f;
    sounds_[SE_ROTATE].isLoop = false;

    sounds_[SE_JUMP].id = Novice::LoadAudio("./Resources/Sounds/SE/jump.mp3");
    sounds_[SE_JUMP].volume = 1.0f;
    sounds_[SE_JUMP].isLoop = false;

    sounds_[SE_DEATH].id = Novice::LoadAudio("./Resources/Sounds/SE/death.mp3");
    sounds_[SE_DEATH].volume = 1.0f;
    sounds_[SE_DEATH].isLoop = false;

    sounds_[SE_KEY_GET].id = Novice::LoadAudio("./Resources/Sounds/SE/key_get.mp3");
    sounds_[SE_KEY_GET].volume = 1.0f;
    sounds_[SE_KEY_GET].isLoop = false;

    sounds_[SE_KEY_UNLOCK].id = Novice::LoadAudio("./Resources/Sounds/SE/key_unlock.mp3");
    sounds_[SE_KEY_UNLOCK].volume = 0.5f;
    sounds_[SE_KEY_UNLOCK].isLoop = false;

    sounds_[SE_GOAL].id = Novice::LoadAudio("./Resources/Sounds/SE/goal.mp3");
    sounds_[SE_GOAL].volume = 3.0f;
    sounds_[SE_GOAL].isLoop = false;

    sounds_[SE_CLEAR].id = Novice::LoadAudio("./Resources/Sounds/SE/clear.mp3");
    sounds_[SE_CLEAR].volume = 1.0f;
    sounds_[SE_CLEAR].isLoop = false;

    /// 
    /// 
    /// ↑ここまで音声設定
};

void SoundHandle::Play(int soundID) {
    Stop(soundID);
    if (sounds_[soundID].id != -1) {
        playHandle_[soundID] = Novice::PlayAudio(sounds_[soundID].id, sounds_[soundID].isLoop, sounds_[soundID].volume);
    }
};

void SoundHandle::Play(int soundID, float volume, bool isLoop) {
    Stop(soundID);
    if (sounds_[soundID].id != -1) {
        playHandle_[soundID] = Novice::PlayAudio(sounds_[soundID].id, isLoop, volume);
    }
};

void SoundHandle::SetVolume(int soundID, float volume) {
    if (playHandle_[soundID] != -1) {
        Novice::SetAudioVolume(playHandle_[soundID], volume);
    }
}

void SoundHandle::Pause(int soundID) {
    if (playHandle_[soundID] != -1) {
        Novice::PauseAudio(playHandle_[soundID]);
    }
}

void SoundHandle::Stop(int soundID) {
    if (playHandle_[soundID] != -1) {
        Novice::StopAudio(playHandle_[soundID]);
    }
}

void SoundHandle::StopAll() {
    for (int i = 0; i < SOUNDS; i++) {
        if (playHandle_[i] != -1) {
            Novice::StopAudio(playHandle_[i]);
        }
    }
}

void SoundPlay(int soundID) {
    SoundHandle::GetInstance()->Play(soundID);
}

void SoundPlay(int soundID, float volume, bool isLoop) {
    SoundHandle::GetInstance()->Play(soundID, volume, isLoop);
}

void SoundSetVolume(int soundID, float volume) {
    SoundHandle::GetInstance()->SetVolume(soundID, volume);
}

void SoundPause(int soundID) {
    SoundHandle::GetInstance()->Pause(soundID);
}

void SoundStop(int soundID) {
    SoundHandle::GetInstance()->Stop(soundID);
}

void SoundStopAll() {
    SoundHandle::GetInstance()->StopAll();
}