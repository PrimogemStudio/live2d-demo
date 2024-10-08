﻿/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "Framework/CubismFramework.hpp"

namespace Live2D { namespace Cubism { namespace Framework {

class CubismModel;

/**
 * @brief Mocデータの管理
 *
 * Mocデータの管理を行うクラス。
 */
class CubismMoc
{
    friend class CubismModel;
public:
    /**
     * @brief バッファからMocデータの作成
     *
     * バッファからMocファイルを読み取り、Mocデータを作成する。
     *
     * @param[in]   mocBytes    Mocファイルのバッファ
     * @param[in]   size        バッファのサイズ
     * @param[in]   shouldCheckMocConsistency MOCの整合性チェックフラグ(初期値 : false)
     */
    static CubismMoc* Create(const csmByte* mocBytes, csmSizeInt size, csmBool shouldCheckMocConsistency = false);

    /**
     * @brief Mocデータを削除
     *
     * Mocデータを削除する。
     */
    static void Delete(CubismMoc* moc);

    /**
     * @brief モデルを作成
     *
     * モデルを作成する。
     *
     * @return  Mocデータから作成されたモデル
     */
    CubismModel* CreateModel();

    /**
     * @brief モデルを削除
     *
     * モデルを削除する。
     *
     * @param[in]   model   対象のモデル
     */
    void DeleteModel(CubismModel* model);

    /**
     * @brief 最新の.moc3 Versionを取得
     *
     * 最新の.moc3 Versionを取得する。
     *
     * @return  最新の.moc3 Version
     */
    static Core::csmMocVersion GetLatestMocVersion();

    /**
     * @brief 読み込んだモデルの.moc3 Versionを取得
     *
     * 読み込んだモデルの.moc3 Versionを取得する。
     *
     * @return  読み込んだモデルの.moc3 Version
     */
    Core::csmMocVersion GetMocVersion();

    /**
     * @brief Checks consistency of a moc.
     *
     * @param  address  Address of unrevived moc. The address must be aligned to 'csmAlignofMoc'.
     * @param  size     Size of moc (in bytes).
     *
     * @return  '1' if Moc is valid; '0' otherwise.
     */
    static csmBool HasMocConsistency(void* address, const csmUint32 size);

    /**
     * @brief Checks consistency of a moc.
     *
     * @param  mocBytes Mocファイルのバッファ
     * @param  size     バッファのサイズ
     *
     * @return  'true' if Moc is valid; 'false' otherwise.
     */
    static csmBool HasMocConsistencyFromUnrevivedMoc(const csmByte* mocBytes, csmSizeInt size);

private:
    /**
     * @brief コンストラクタ
     *
     * コンストラクタ。
     */
    CubismMoc(Core::csmMoc* moc);

    /**
     * @brief デストラクタ
     *
     * デストラクタ。
     */
    virtual ~CubismMoc();

    Core::csmMoc*     _moc;             ///< Mocデータ
    csmInt32          _modelCount;      ///< Mocデータから作られたモデルの個数
    csmUint32         _mocVersion;      ///< 読み込んだモデルの.moc3 Version
};

}}}
