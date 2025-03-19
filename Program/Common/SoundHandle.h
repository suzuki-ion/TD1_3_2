#pragma once
#include "Structures.h"

// ID名は先頭に必ず効果音なら SE_、曲なら BGM_ と付ける
enum SoundsID {
    SOUND_NONE,

    /// 
    /// ↓ここからID記述
    /// 
    
    BGM_TITLE,
    BGM_STAGE_SELECT,
    BGM_GAME,

    SE_SELECT,
    SE_DECIDE,

    SE_STOP,
    SE_START,
    SE_ROTATE,
    SE_JUMP,
    SE_DEATH,

    SE_KEY_GET,
    SE_KEY_UNLOCK,

	SE_GOAL,
    SE_CLEAR,

    /// 
    /// ↑ここまでID記述
    /// 

    // 音声の総数
    SOUNDS
};

/// @brief サウンドハンドル
class SoundHandle {
public:
    SoundHandle(const SoundHandle &) = delete;
    SoundHandle &operator=(const SoundHandle &) = delete;
    SoundHandle(SoundHandle &&) = delete;
    SoundHandle &operator=(SoundHandle &&) = delete;

    /// @brief サウンドハンドルのインスタンス取得
    /// @return サウンドハンドルのインスタンス
    static SoundHandle *GetInstance() {
        static SoundHandle instance;
        return &instance;
    }

    /// @brief 音声の読み込み用関数。これは GrapgHandle と違って Unload ができないためゲーム中に実行しても再読み込み不可。
    void Load();

    /// @brief 音声再生用関数(デフォルト値を使用)
    /// @param soundID 再生する音声のID
    void Play(int soundID);

    /// @brief 音声再生用関数(音量・ループフラグ指定)
    /// @param soundID 再生する音声のID
    /// @param volume 音量(0.0f ~ 1.0f)
    /// @param isLoop ループフラグ
    void Play(int soundID, float volume, bool isLoop);

    /// @brief 音量変更用関数
    /// @param soundID 再生中の音声のID
    /// @param volume 音量(0.0f ~ 1.0f)
    void SetVolume(int soundID, float volume);

    /// @brief 音声一時停止用関数
    /// @param soundID 一時停止する音声のID
    void Pause(int soundID);

    /// @brief 音声再生停止用関数
    /// @param soundID 停止する音声のID
    void Stop(int soundID);

    /// @brief 全音声再生停止用関数
    void StopAll();

private:
    SoundHandle() = default;
    ~SoundHandle() = default;

    // 音声のハンドル
    Sound sounds_[SOUNDS];
    // 再生用ハンドル
    int playHandle_[SOUNDS];
};

/// @brief 音声再生用関数(デフォルト値を使用)
/// @param soundID 再生する音声のID
void SoundPlay(int soundID);

/// @brief 音声再生用関数(音量・ループフラグ指定)
/// @param soundID 再生する音声のID
void SoundPlay(int soundID, float volume, bool isLoop);

/// @brief 音量変更用関数
/// @param soundID 再生中の音声のID
/// @param volume 音量(0.0f ~ 1.0f)
void SoundSetVolume(int soundID, float volume);

/// @brief 音声一時停止用関数
/// @param soundID 一時停止する音声のID
void SoundPause(int soundID);

/// @brief 音声再生停止用関数
/// @param soundID 停止する音声のID
void SoundStop(int soundID);

/// @brief 全音声再生停止用関数
void SoundStopAll();