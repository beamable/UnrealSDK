// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBallAssetManager.h"

void UBeamBallAssetManager::CacheAsset(FString Key, UObject* Asset)
{
	if (!LoadedAssets.Contains(Key))
	{
		LoadedAssets.Add(Key, Asset);
	}

	if (OnContentLoaded.Contains(Key))
	{
		for (auto ContentDelegate : OnContentLoaded[Key])
		{
			ContentDelegate.ExecuteIfBound(Asset);
		}
		OnContentLoaded.Remove(Key);
	}
	if (OnContentLoadedCode.Contains(Key))
	{
		for (auto ContentDelegate : OnContentLoadedCode[Key])
		{
			ContentDelegate.ExecuteIfBound(Asset);
		}
		OnContentLoadedCode.Remove(Key);
	}
}

void UBeamBallAssetManager::GetLoadedAssets(FString Key, FOnBeamContentLoaded OnLoadedAsset)
{
	if (LoadedAssets.Contains(Key))
	{
		OnLoadedAsset.ExecuteIfBound(LoadedAssets[Key]);
	}else
	{
		for (auto Tuple : OnContentLoaded)
		{
			if (Tuple.Value.Contains(OnLoadedAsset))
			{
				OnContentLoaded[Tuple.Key].Remove(OnLoadedAsset);
				break;
			}
		}
		if (OnContentLoaded.Contains(Key))
		{
			OnContentLoaded[Key].Add(OnLoadedAsset);
		}else
		{
			OnContentLoaded.Add(Key, {OnLoadedAsset});
		}
	}
}

void UBeamBallAssetManager::GetLoadedAssets(FString Key, FOnBeamContentLoadedCode OnLoadedAsset)
{
	if (LoadedAssets.Contains(Key))
	{
		OnLoadedAsset.ExecuteIfBound(LoadedAssets[Key]);
	}else
	{
		if (OnContentLoadedCode.Contains(Key))
		{
			OnContentLoadedCode[Key].Add(OnLoadedAsset);
		}else
		{
			OnContentLoadedCode.Add(Key, {OnLoadedAsset});
		}
	}
}
