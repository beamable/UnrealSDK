// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Content/BeamContentSubsystem.h"


#include "HttpModule.h"
#include "BeamBackend/BeamGenericApi.h"
#include "BeamNotifications/SubSystems/BeamContentNotifications.h"
#include "Interfaces/IHttpResponse.h"
#include "Content/DownloadContentState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"
#include "UObject/UObjectGlobals.h"

#if WITH_EDITOR
#include "BeamableCoreRuntimeEditor/Public/Subsystems/Content/BeamEditorContent.h"
#endif

void DescendLookingForContentLinks(const FString& TypeName, const FString& ContentTypeId, const FProperty* Property, TArray<const FProperty*>& TreePath,
                                   TArray<TArray<const FProperty*>>& FoundPathsToLinks,
                                   TArray<TArray<const FProperty*>>& FoundPathsToRecursiveProps, TArray<UClass*>& FoundRecursiveTypes)
{
	TreePath.Push(Property);

	TArray<FString> PathToProp;
	for (const FProperty* PathLink : TreePath)
		PathToProp.Add(PathLink->GetName());
	const auto PathStr = FString::Join(PathToProp, TEXT("."));

	// Recursive DFS of the property tree 
	if (const auto StructProperty = CastField<FStructProperty>(Property))
	{
		// TODO: Leaf nodes should be either FBeamContentLink OR FOptionalBeamContentLink (we should then handle both these leaf properties at runtime) 
		if (StructProperty->Struct == FBeamContentLink::StaticStruct())
		{
			// Copy the current tree path into the output paths to ContentLinks.
			FoundPathsToLinks.Add(TArray{TreePath});
			UE_LOG(LogBeamContent, Verbose, TEXT("Found Content Link in ContentType - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s"), *TypeName, *ContentTypeId, *PathStr);
		}
		else
		{
			for (TFieldIterator<FProperty> ObjPropIt(StructProperty->Struct); ObjPropIt; ++ObjPropIt)
			{
				UE_LOG(LogBeamContent, Verbose, TEXT("Starting with Struct Field - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
				DescendLookingForContentLinks(TypeName, ContentTypeId, *ObjPropIt, TreePath, FoundPathsToLinks, FoundPathsToRecursiveProps, FoundRecursiveTypes);
				UE_LOG(LogBeamContent, Verbose, TEXT("Done with Struct Field - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
			}
		}
	}
	else if (CastField<FClassProperty>(Property))
	{
		// We do nothing when we bump into UClass fields here.
		return;
	}
	else if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		// We do not need to go looking through recursive types.
		const auto bIsRootType = ObjectProperty->PropertyClass.GetName().Equals(TypeName);
		if (const int32 RecursiveIdx = TreePath.IndexOfByPredicate([Property](const FProperty* PropInTree) { return PropInTree->SameType(Property); }); RecursiveIdx != INDEX_NONE || bIsRootType)
		{
			FoundPathsToRecursiveProps.Add(TArray{TreePath});
			FoundRecursiveTypes.Add(ObjectProperty->PropertyClass);

			UE_LOG(LogBeamContent,
			       Verbose,
			       TEXT(
				       "Found recursive property inside a UObject field (the type of this property has a pointer to itself). We process this as a special case later. - TYPE=%s, TYPE_ID=%s, PATH_TO_RECURSIVE_FIELD=%s, RECURSIVE_TYPE=%s"
			       ),
			       *TypeName, *ContentTypeId, *PathStr, *ObjectProperty->PropertyClass.GetName()
			);
			TreePath.Pop();
			return;
		}

		for (TFieldIterator<FProperty> ObjPropIt(ObjectProperty->PropertyClass); ObjPropIt; ++ObjPropIt)
		{
			UE_LOG(LogBeamContent, Verbose, TEXT("Start with Object Field - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
			DescendLookingForContentLinks(TypeName, ContentTypeId, *ObjPropIt, TreePath, FoundPathsToLinks, FoundPathsToRecursiveProps, FoundRecursiveTypes);
			UE_LOG(LogBeamContent, Verbose, TEXT("Start with Object Field - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
		}
	}
	// If its an array of structs or objects, we descend into the array's type.
	else if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		if (CastField<FClassProperty>(Property))
		{
			// We do nothing when we bump into UClass fields here.
			return;
		}

		if (const auto ArrayObjectProperty = CastField<FObjectProperty>(ArrayProperty->Inner))
		{
			// We do not need to go looking through recursive types.
			const auto bIsRootType = ArrayObjectProperty->PropertyClass.GetName().Equals(TypeName);
			const int32 RecursiveIdx = TreePath.IndexOfByPredicate([ArrayObjectProperty](const FProperty* PropInTree)
			{
				if (const auto InTree = CastField<FObjectProperty>(PropInTree)) return InTree->PropertyClass == ArrayObjectProperty->PropertyClass;
				return false;
			});

			if (RecursiveIdx != INDEX_NONE || bIsRootType)
			{
				FoundPathsToRecursiveProps.Add(TArray{TreePath});
				FoundRecursiveTypes.Add(ArrayObjectProperty->PropertyClass);

				UE_LOG(LogBeamContent,
				       Verbose,
				       TEXT(
					       "Found recursive property inside an array's type (the type of this property has a pointer to itself). We process this as a special case later. - TYPE=%s, TYPE_ID=%s, PATH_TO_RECURSIVE_FIELD=%s, RECURSIVE_TYPE=%s"
				       ),
				       *TypeName, *ContentTypeId, *PathStr, *ArrayObjectProperty->PropertyClass.GetName());

				TreePath.Pop();
				return;
			}

			for (TFieldIterator<FProperty> ObjPropIt(ArrayObjectProperty->PropertyClass); ObjPropIt; ++ObjPropIt)
			{
				UE_LOG(LogBeamContent, Verbose, TEXT("Start with Object Field [Array] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
				DescendLookingForContentLinks(TypeName, ContentTypeId, *ObjPropIt, TreePath, FoundPathsToLinks, FoundPathsToRecursiveProps, FoundRecursiveTypes);
				UE_LOG(LogBeamContent, Verbose, TEXT("End with Object Field [Array] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
			}
		}

		if (const auto ArrayStructProperty = CastField<FStructProperty>(ArrayProperty->Inner))
		{
			if (ArrayStructProperty->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
			{
				// Copy the current tree path into the output paths to ContentLinks.
				FoundPathsToLinks.Add(TArray{TreePath});
				UE_LOG(LogBeamContent, Verbose, TEXT("Found Content Link Array in ContentType  - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s"), *TypeName, *ContentTypeId, *PathStr);
			}
			else
			{
				for (TFieldIterator<FProperty> ObjPropIt(ArrayStructProperty->Struct); ObjPropIt; ++ObjPropIt)
				{
					UE_LOG(LogBeamContent, Verbose, TEXT("Start with Struct Field [Array] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
					DescendLookingForContentLinks(TypeName, ContentTypeId, *ObjPropIt, TreePath, FoundPathsToLinks, FoundPathsToRecursiveProps, FoundRecursiveTypes);
					UE_LOG(LogBeamContent, Verbose, TEXT("End with Struct Field [Array] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
				}
			}
		}
	}
	// If its an map of FString, we descend into the map's value type.
	else if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		if (CastField<FClassProperty>(Property))
		{
			// We do nothing when we bump into UClass fields here.
			return;
		}

		if (const auto MapObjectProperty = CastField<FObjectProperty>(MapProperty->ValueProp))
		{
			// We do not need to go looking through recursive types.
			const auto bIsRootType = MapObjectProperty->PropertyClass.GetName().Equals(TypeName);
			const int32 RecursiveIdx = TreePath.IndexOfByPredicate([MapObjectProperty](const FProperty* PropInTree)
			{
				if (const auto InTree = CastField<FObjectProperty>(PropInTree)) return InTree->PropertyClass == MapObjectProperty->PropertyClass;
				return false;
			});

			if (RecursiveIdx != INDEX_NONE || bIsRootType)
			{
				FoundPathsToRecursiveProps.Add(TArray{TreePath});
				FoundRecursiveTypes.Add(MapObjectProperty->PropertyClass);

				UE_LOG(LogBeamContent,
				       Verbose,
				       TEXT(
					       "Found recursive property inside a map's value type (the type of this property has a pointer to itself). We process this as a special case later. - TYPE=%s, TYPE_ID=%s, PATH_TO_RECURSIVE_FIELD=%s, RECURSIVE_TYPE=%s"
				       ),
				       *TypeName, *ContentTypeId, *PathStr, *MapObjectProperty->PropertyClass.GetName());

				TreePath.Pop();
				return;
			}

			for (TFieldIterator<FProperty> ObjPropIt(MapObjectProperty->PropertyClass); ObjPropIt; ++ObjPropIt)
			{
				UE_LOG(LogBeamContent, Verbose, TEXT("Start with Object Field [Map] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
				DescendLookingForContentLinks(TypeName, ContentTypeId, *ObjPropIt, TreePath, FoundPathsToLinks, FoundPathsToRecursiveProps, FoundRecursiveTypes);
				UE_LOG(LogBeamContent, Verbose, TEXT("End with Object Field [Map] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
			}
		}

		if (const auto MapStructProperty = CastField<FStructProperty>(MapProperty->ValueProp))
		{
			if (MapStructProperty->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
			{
				// Copy the current tree path into the output paths to ContentLinks.
				FoundPathsToLinks.Add(TArray{TreePath});
				UE_LOG(LogBeamContent, Verbose, TEXT("Found Content Link Map in ContentType - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s"), *TypeName, *ContentTypeId, *PathStr);
			}
			else
			{
				for (TFieldIterator<FProperty> ObjPropIt(MapStructProperty->Struct); ObjPropIt; ++ObjPropIt)
				{
					UE_LOG(LogBeamContent, Verbose, TEXT("Start with Struct Field [Map] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
					DescendLookingForContentLinks(TypeName, ContentTypeId, *ObjPropIt, TreePath, FoundPathsToLinks, FoundPathsToRecursiveProps, FoundRecursiveTypes);
					UE_LOG(LogBeamContent, Verbose, TEXT("End with Struct Field [Map] - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s.%s"), *TypeName, *ContentTypeId, *PathStr, *ObjPropIt->GetName());
				}
			}
		}
	}
	else
	{
		UE_LOG(LogBeamContent, Verbose, TEXT("Skipping Property as isn't a Content Link and can't contain one - TYPE=%s, TYPE_ID=%s, PATH_TO_FIELD=%s"), *TypeName, *ContentTypeId,
		       *FString::Join(PathToProp, TEXT(".")));
	}
	TreePath.Pop();
}

void ChaseContentLinkProperty(void* RootObj, TArray<const FProperty*> PathToLink, TArray<FBeamContentId>& OutLinksToFetch)
{
	if (!PathToLink.Num()) return;

	// Build the path to the content link from the recursive property root.	
	TArray<FString> PathStr;
	FBeamContentLink FoundLink;

	const auto CurrProp = PathToLink[0];

	if (CastField<FClassProperty>(CurrProp))
	{
		// We do nothing when we bump into UClass fields here.
		return;
	}

	if (const auto StructProp = CastField<FStructProperty>(CurrProp))
	{
		if (StructProp->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
		{
			StructProp->GetValue_InContainer(RootObj, &FoundLink);
			OutLinksToFetch.AddUnique(FBeamContentId{FoundLink.AsString});

			UE_LOG(LogBeamContent, Verbose, TEXT("Found Content Link with Id. CONTENT_LINK_ID=%s"), *FoundLink.AsString);
			return;
		}

		int32 Size = StructProp->Struct->GetPropertiesSize();
		int32 Alignment = StructProp->Struct->GetMinAlignment();

		uint8* StructCopy = (uint8*)FMemory::Malloc(Size, Alignment);
		FMemory::Memzero(StructCopy, Size);

		if (!StructProp->HasAnyPropertyFlags(CPF_ZeroConstructor))
			StructProp->InitializeValue_InContainer(StructCopy);

		StructProp->GetValue_InContainer(RootObj, StructCopy);

		PathToLink.RemoveAt(0);
		ChaseContentLinkProperty(StructCopy, PathToLink, OutLinksToFetch);
		FMemory::Free(StructCopy);
		return;
	}

	if (const auto ObjProp = CastField<FObjectProperty>(CurrProp))
	{
		if (const auto Obj = ObjProp->GetObjectPropertyValue_InContainer(RootObj))
		{
			PathToLink.RemoveAt(0);
			ChaseContentLinkProperty(Obj, PathToLink, OutLinksToFetch);
		}
		return;
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(CurrProp))
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(RootObj));
		FScriptArrayHelper ArrayHelper(ArrayProperty, Val);

		if (CastField<FClassProperty>(ArrayProperty->Inner))
		{
			// We do nothing when we bump into UClass fields here.
			return;
		}

		if (const auto ArrayStructProp = CastField<FStructProperty>(ArrayProperty->Inner))
		{
			if (ArrayStructProp->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
			{
				for (int i = 0; i < ArrayHelper.Num(); ++i)
				{
					const FBeamContentLink* Data = reinterpret_cast<const FBeamContentLink*>(ArrayHelper.GetRawPtr(i));
					const FString* UnderlyingString = static_cast<const FString*>(Data->GetAddr(0));
					OutLinksToFetch.AddUnique(FBeamContentId{*UnderlyingString});
					UE_LOG(LogBeamContent, Warning, TEXT("Found Content Link with Id inside Array. CONTENT_LINK_ID=%s"), *Data->AsString);
				}
				return;
			}

			PathToLink.RemoveAt(0);
			for (int Index = 0; Index < ArrayHelper.Num(); ++Index)
			{
				const auto StructPtr = ArrayHelper.GetRawPtr(Index);
				ChaseContentLinkProperty(StructPtr, PathToLink, OutLinksToFetch);
			}
		}

		if (CastField<FObjectProperty>(ArrayProperty->Inner))
		{
			PathToLink.RemoveAt(0);
			for (int Index = 0; Index < ArrayHelper.Num(); ++Index)
			{
				if (UObject* InstancedObject = *reinterpret_cast<UObject**>(ArrayHelper.GetRawPtr(Index)))
				{
					ChaseContentLinkProperty(InstancedObject, PathToLink, OutLinksToFetch);
				}
			}
		}
		return;
	}

	if (const auto MapProperty = CastField<FMapProperty>(CurrProp))
	{
		const FScriptMap* Val = MapProperty->GetPropertyValuePtr(MapProperty->ContainerPtrToValuePtr<void>(RootObj));
		FScriptMapHelper MapHelper(MapProperty, Val);

		if (CastField<FClassProperty>(MapProperty->ValueProp))
		{
			// We do nothing when we bump into UClass fields here.
			return;
		}

		if (const auto MapStructProp = CastField<FStructProperty>(MapProperty->ValueProp))
		{
			if (MapStructProp->Struct->IsChildOf(FBeamContentLink::StaticStruct()))
			{
				for (int i = 0; i < MapHelper.Num(); ++i)
				{
					const FBeamContentLink* Data = reinterpret_cast<const FBeamContentLink*>(MapHelper.GetValuePtr(i));
					const FString* UnderlyingString = static_cast<const FString*>(Data->GetAddr(0));
					OutLinksToFetch.AddUnique(FBeamContentId{*UnderlyingString});
					UE_LOG(LogBeamContent, Warning, TEXT("Found Content Link with Id inside Map. CONTENT_LINK_ID=%s"), *Data->AsString);
				}
				return;
			}

			PathToLink.RemoveAt(0);
			for (int Index = 0; Index < MapHelper.Num(); ++Index)
			{
				const auto StructPtr = MapHelper.GetValuePtr(Index);
				ChaseContentLinkProperty(StructPtr, PathToLink, OutLinksToFetch);
			}
		}

		if (CastField<FObjectProperty>(MapProperty->ValueProp))
		{
			PathToLink.RemoveAt(0);
			for (int Index = 0; Index < MapHelper.Num(); ++Index)
			{
				if (UObject* InstancedObject = *reinterpret_cast<UObject**>(MapHelper.GetValuePtr(Index)))
				{
					ChaseContentLinkProperty(InstancedObject, PathToLink, OutLinksToFetch);
				}
			}
		}
	}
}

void ChaseRecursiveRoots(UClass* RecursiveType, const TArray<TArray<const FProperty*>>& PathsToRecursiveSelvesFromRecursiveRoot, TArray<const FProperty*> CurrentPathToSelfFromRoot, void* RootObj,
                         TArray<UObject*>& OutRecursiveRoots)
{
	if (!CurrentPathToSelfFromRoot.Num()) return;

	// Build the path to the content link from the recursive property root.	
	TArray<FString> PathStr;
	FBeamContentLink FoundLink;

	const auto CurrProp = CurrentPathToSelfFromRoot[0];


	if (CastField<FClassProperty>(CurrProp))
	{
		// We do nothing when we bump into UClass fields here.
		return;
	}

	if (const auto StructProp = CastField<FStructProperty>(CurrProp))
	{
		int32 Size = StructProp->Struct->GetPropertiesSize();
		int32 Alignment = StructProp->Struct->GetMinAlignment();

		uint8* StructCopy = (uint8*)FMemory::Malloc(Size, Alignment);
		FMemory::Memzero(StructCopy, Size);

		if (!StructProp->HasAnyPropertyFlags(CPF_ZeroConstructor))
			StructProp->InitializeValue_InContainer(StructCopy);

		StructProp->GetValue_InContainer(RootObj, StructCopy);

		CurrentPathToSelfFromRoot.RemoveAt(0);
		ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, CurrentPathToSelfFromRoot, StructCopy, OutRecursiveRoots);
		FMemory::Free(StructCopy);
		return;
	}

	if (const auto ObjProp = CastField<FObjectProperty>(CurrProp))
	{
		if (const auto InstancedObject = ObjProp->GetObjectPropertyValue_InContainer(RootObj))
		{
			if (RecursiveType == ObjProp->PropertyClass)
			{
				OutRecursiveRoots.Add(InstancedObject);
				for (const auto& ToRecursiveSelvesFromRecursiveRoot : PathsToRecursiveSelvesFromRecursiveRoot)
				{
					ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, ToRecursiveSelvesFromRecursiveRoot, InstancedObject, OutRecursiveRoots);
				}
			}
			else
			{
				CurrentPathToSelfFromRoot.RemoveAt(0);
				ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, CurrentPathToSelfFromRoot, InstancedObject, OutRecursiveRoots);
			}
		}
		return;
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(CurrProp))
	{
		const FScriptArray* Val = ArrayProperty->GetPropertyValuePtr(ArrayProperty->ContainerPtrToValuePtr<void>(RootObj));
		FScriptArrayHelper ArrayHelper(ArrayProperty, Val);

		if (const auto ArrayStructProp = CastField<FStructProperty>(ArrayProperty->Inner))
		{
			CurrentPathToSelfFromRoot.RemoveAt(0);
			for (int Index = 0; Index < ArrayHelper.Num(); ++Index)
			{
				const auto StructPtr = ArrayHelper.GetRawPtr(Index);
				ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, CurrentPathToSelfFromRoot, StructPtr, OutRecursiveRoots);
			}
		}
		else if (CastField<FClassProperty>(ArrayProperty->Inner))
		{
			// We do nothing when we bump into UClass fields here.
			return;
		}
		else if (const auto ArrayObjProp = CastField<FObjectProperty>(ArrayProperty->Inner))
		{
			CurrentPathToSelfFromRoot.RemoveAt(0);
			for (int Index = 0; Index < ArrayHelper.Num(); ++Index)
			{
				if (UObject* InstancedObject = *reinterpret_cast<UObject**>(ArrayHelper.GetRawPtr(Index)))
				{
					if (RecursiveType == ArrayObjProp->PropertyClass)
					{
						OutRecursiveRoots.Add(InstancedObject);
						for (const auto& ToRecursiveSelvesFromRecursiveRoot : PathsToRecursiveSelvesFromRecursiveRoot)
						{
							ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, ToRecursiveSelvesFromRecursiveRoot, InstancedObject, OutRecursiveRoots);
						}
					}
					else
					{
						CurrentPathToSelfFromRoot.RemoveAt(0);
						ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, CurrentPathToSelfFromRoot, InstancedObject, OutRecursiveRoots);
					}
				}
			}
		}
		return;
	}

	if (const auto MapProperty = CastField<FMapProperty>(CurrProp))
	{
		const FScriptMap* Val = MapProperty->GetPropertyValuePtr(MapProperty->ContainerPtrToValuePtr<void>(RootObj));
		FScriptMapHelper MapHelper(MapProperty, Val);

		if (const auto MapStructProp = CastField<FStructProperty>(MapProperty->ValueProp))
		{
			CurrentPathToSelfFromRoot.RemoveAt(0);
			for (int Index = 0; Index < MapHelper.Num(); ++Index)
			{
				const auto StructPtr = MapHelper.GetValuePtr(Index);
				ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, CurrentPathToSelfFromRoot, StructPtr, OutRecursiveRoots);
			}
		}
		else if (CastField<FClassProperty>(MapProperty->ValueProp))
		{
			// We do nothing when we bump into UClass fields here.
			return;
		}
		else if (const auto MapObjProp = CastField<FObjectProperty>(MapProperty->ValueProp))
		{
			CurrentPathToSelfFromRoot.RemoveAt(0);
			for (int Index = 0; Index < MapHelper.Num(); ++Index)
			{
				if (UObject* InstancedObject = *reinterpret_cast<UObject**>(MapHelper.GetValuePtr(Index)))
				{
					if (RecursiveType == MapObjProp->PropertyClass)
					{
						OutRecursiveRoots.Add(InstancedObject);
						for (const auto& ToRecursiveSelvesFromRecursiveRoot : PathsToRecursiveSelvesFromRecursiveRoot)
						{
							ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, ToRecursiveSelvesFromRecursiveRoot, InstancedObject, OutRecursiveRoots);
						}
					}
					else
					{
						CurrentPathToSelfFromRoot.RemoveAt(0);
						ChaseRecursiveRoots(RecursiveType, PathsToRecursiveSelvesFromRecursiveRoot, CurrentPathToSelfFromRoot, InstancedObject, OutRecursiveRoots);
					}
				}
			}
		}
		return;
	}
}

void UBeamContentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ContentApi = GEngine->GetEngineSubsystem<UBeamContentApi>();
	GenericApi = GEngine->GetEngineSubsystem<UBeamGenericApi>();
}

void UBeamContentSubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	// Grab all existing ContentObject classes so we can correctly deserialize content we fetch from the content API.
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UBeamContentObject::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			FString TypeName = It->GetFName().ToString();
			FString ContentTypeId = It->GetDefaultObject<UBeamContentObject>()->BuildContentTypeString();

			UClass* ContentTypeClass = *It;

			UE_LOG(LogTemp, Display, TEXT("Initializing Beam Runtime Content System - TYPE=%s, TYPE_ID=%s"), *TypeName, *ContentTypeId);
			AllContentTypes.Add(ContentTypeClass);
			ContentTypeStringToContentClass.Add(ContentTypeId, ContentTypeClass);
			ContentClassToContentTypeString.Add(ContentTypeClass, ContentTypeId);


			// Map paths to FBeamContentLink recursively descending into all USTRUCT/UOBJECTS
			TArray<const FProperty*> TreePath;
			TArray<TArray<const FProperty*>> FoundPathsToLinks;
			TArray<TArray<const FProperty*>> FoundPathsToRecursiveProps;
			TArray<UClass*> RecursiveTypes;
			for (TFieldIterator<FProperty> PropIt(ContentTypeClass); PropIt; ++PropIt)
			{
				UE_LOG(LogBeamContent, Verbose, TEXT("Starting From Field - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s"), *TypeName, *ContentTypeId, *PropIt->GetName());
				DescendLookingForContentLinks(TypeName, ContentTypeId, *PropIt, TreePath, FoundPathsToLinks, FoundPathsToRecursiveProps, RecursiveTypes);
				TreePath.Reset();
				UE_LOG(LogBeamContent, Verbose, TEXT("Done with Field - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s"), *TypeName, *ContentTypeId, *PropIt->GetName());
			}
			// Store the path of properties I need to chase to get to the link property.
			for (TArray<const FProperty*> FoundPathsToLink : FoundPathsToLinks)
			{
				TArray<FString> PathToProp;
				for (const FProperty* PathLink : FoundPathsToLink)
					PathToProp.Add(PathLink->GetName());

				UE_LOG(LogBeamContent, Verbose, TEXT("Found Content Link in ContentType - TYPE=%s, TYPE_ID=%s, PATH_TO_LINK_FIELD=%s"), *TypeName, *ContentTypeId,
				       *FString::Join(PathToProp, TEXT(".")));
			}
			PathsToContentLinks.Add(ContentTypeClass, TArray{FoundPathsToLinks});

			// Store any recursive properties of this content type so we can build and match against the "paths from recursive type" to see if we need to descend a recursive structure looking for links
			const auto NumOfRecursiveProps = FoundPathsToRecursiveProps.Num();
			for (int i = 0; i < NumOfRecursiveProps; ++i)
			{
				const auto FoundPathToRecursiveProp = FoundPathsToRecursiveProps[i];
				const auto RecursiveType = RecursiveTypes[i];

				TArray<TArray<const FProperty*>> FoundPathsToLinksFromRecursiveTypes;
				TArray<TArray<const FProperty*>> FoundPathsToRecursiveSelf;
				TArray<UClass*> RecursiveRootTypes;

				// If we have not descended this type at some point already, we need to descend it.
				if (!PathsToContentLinks.Contains(RecursiveType))
				{
					for (TFieldIterator<FProperty> PropIt(RecursiveType); PropIt; ++PropIt)
					{
						DescendLookingForContentLinks(RecursiveType->GetName(), ContentTypeId, *PropIt, TreePath, FoundPathsToLinksFromRecursiveTypes, FoundPathsToRecursiveSelf, RecursiveRootTypes);
						TreePath.Reset();
					}

					// Store the paths to ContentLinks from this recursive property as a root.
					PathsToContentLinks.Add(RecursiveType, FoundPathsToLinksFromRecursiveTypes);

					// Store the paths to all fields of type RecursiveType (TArray<URecursiveType*> and TMap<FString, URecursiveType*>) from the RecursiveType itself 
					PathsToRecursiveSelves.Add(RecursiveType, FoundPathsToRecursiveSelf);
				}

				// If the recursive prop's type has content links inside it, we need to keep track of this so we can correctly gather links when downloading content. 
				if (PathsToContentLinks[RecursiveType].Num() > 0)
				{
					// Build the path to the recursive property
					TArray<FString> PathToRecursiveProp;
					for (const FProperty* PathLink : FoundPathToRecursiveProp) PathToRecursiveProp.Add(PathLink->GetName());
					const auto PathToRecursivePropStr = FString::Join(PathToRecursiveProp, TEXT("."));

					// For each of the paths to content links that we found inside the recursive properties...
					for (TArray<const FProperty*> FoundPathsToLink : FoundPathsToLinksFromRecursiveTypes)
					{
						// Build the path to the content link from the recursive property root.
						TArray<FString> PathToProp;
						for (const FProperty* PathLink : FoundPathsToLink) PathToProp.Add(PathLink->GetName());
						const auto PathToLink = FString::Join(PathToProp, TEXT("."));

						// Log out the found recursive type and the path for its property.
						UE_LOG(LogBeamContent, Verbose,
						       TEXT(
							       "Found Content Link in RecursiveType inside ContentType. - TYPE=%s, TYPE_ID=%s, PATH_TO_RECURSIVE_PROP=%s, RECURSIVE_TYPE=%s, PATH_TO_LINK_FIELD_IN_RECURSIVE_TYPE=%s"
						       ),
						       *TypeName, *ContentTypeId, *PathToRecursivePropStr, *RecursiveType->GetName(), *PathToLink);
					}

					// For each of the paths to content links that we found inside the recursive properties...
					for (TArray<const FProperty*> FoundPathsToLink : FoundPathsToRecursiveSelf)
					{
						// Build the path to the content link from the recursive property root.
						TArray<FString> PathToProp;
						for (const FProperty* PathLink : FoundPathsToLink) PathToProp.Add(PathLink->GetName());
						const auto PathToLink = FString::Join(PathToProp, TEXT("."));

						// Log out the found recursive type and the path for its property.
						UE_LOG(LogBeamContent, Verbose,
						       TEXT(
							       "Found Recursive Prop in RecursiveType inside ContentType. - TYPE=%s, TYPE_ID=%s, PATH_TO_RECURSIVE_PROP=%s, RECURSIVE_TYPE=%s, PATH_TO_LINK_FIELD_IN_RECURSIVE_TYPE=%s"
						       ),
						       *TypeName, *ContentTypeId, *PathToRecursivePropStr, *RecursiveType->GetName(), *PathToLink);
					}

					// Store the path to this recursive property
					if (PathsToRecursiveProperties.Contains(ContentTypeClass)) PathsToRecursiveProperties[ContentTypeClass].Add(FoundPathToRecursiveProp);
					else PathsToRecursiveProperties.Add(ContentTypeClass, TArray<TArray<const FProperty*>>{FoundPathToRecursiveProp});

					// Store the type of this recursive property
					if (RecursivePropertyTypes.Contains(ContentTypeClass)) RecursivePropertyTypes[ContentTypeClass].Add(RecursiveType);
					else RecursivePropertyTypes.Add(ContentTypeClass, TArray{RecursiveType});
				}
			}
		}
	}

	// Go through list of baked content manifests and load up the baked BeamRuntimeContentCache the baked		
	auto CoreSettings = GetMutableDefault<UBeamCoreSettings>();
	auto RuntimeSettings = GetMutableDefault<UBeamRuntimeSettings>();

	FBeamOperationHandle Op = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({}, GetName(), {});

	//Try to load the cached content first before the baked content
	const FString CachedContentPath = FPaths::ProjectSavedDir() + CoreSettings->CachedContentFolderName + "/" +
		CoreSettings->GlobalCachedContentFileName;

	bool bFoundDataInCacheFile = false;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*CachedContentPath))
	{
		// Load the file data into an array
		TArray<uint8> FileData;
		if (FFileHelper::LoadFileToArray(FileData, *CachedContentPath))
		{
			UBeamContentCache* LoadedCacheContent = NewObject<UBeamContentCache>();

			// Create a memory reader to read the binary data			
			FBeamMemoryReader Reader(FileData, true);

			if (LoadedCacheContent->SerializeToBinary(Reader, ContentTypeStringToContentClass, ContentClassToContentTypeString))
			{
				bFoundDataInCacheFile = true;

				BakedContent.Add(LoadedCacheContent->ManifestId, LoadedCacheContent);
				LiveContent.Add(LoadedCacheContent->ManifestId, DuplicateObject<UBeamContentCache>(LoadedCacheContent, GetTransientPackage()));


				UE_LOG(LogBeamContent, Log, TEXT("Found content in the cached files"));

				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
			}
		}
	}


	//if we didn't find cached data use the baked data
	if (!bFoundDataInCacheFile)
	{
		const FString BakedContentPath = FPaths::ProjectContentDir() + CoreSettings->BakedContentFolderName + "/" +
			CoreSettings->GlobalBakedContentFileName;

		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*BakedContentPath))
		{
			// Load the file data into an array
			TArray<uint8> FileData;
			if (FFileHelper::LoadFileToArray(FileData, *BakedContentPath))
			{
				UBeamContentCache* LoadedBakedContent = NewObject<UBeamContentCache>();

				FBeamMemoryReader Reader(FileData, true);

				if (LoadedBakedContent->SerializeToBinary(Reader, ContentTypeStringToContentClass, ContentClassToContentTypeString))
				{
					BakedContent.Add(LoadedBakedContent->ManifestId, LoadedBakedContent);
					LiveContent.Add(LoadedBakedContent->ManifestId, DuplicateObject<UBeamContentCache>(LoadedBakedContent, GetTransientPackage()));

					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});

					UE_LOG(LogBeamContent, Log, TEXT("Found content in the baked files"));
				}
				else
				{
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op,TEXT("Data found in the baked file was corrupted or inconsistent with current version"));
					GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
				}
			}
			else
			{
				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op,TEXT("Error while reading the baked content file"));
				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
			}
		}
		else
		{
			// If we don't have any baked content, this Operation is a no-op.
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
		}
	}

	ResultOp = Op;
}

void UBeamContentSubsystem::OnBeamableStarting_Implementation(FBeamOperationHandle& ResultOp)
{
	FBeamOperationHandle Op = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({}, GetName(), {});

	const auto ManifestId = FBeamContentManifestId{TEXT("global")};
	const auto bShouldDownloadIndividuals = GetDefault<UBeamRuntimeSettings>()->bDownloadIndividualContentOnStart;
	FetchContentManifest(ManifestId, bShouldDownloadIndividuals, false, Op);
	ResultOp = Op;
}

void UBeamContentSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	// The result Op is a completed Op as we don't have anything else to do async if we are not fetching content.
	Super::OnUserSignedIn_Implementation(UserSlot, BeamRealmUser, bIsOwnerUserAuth, ResultOp);

	// We also set up the content refresh notification here whenever the owner user signs in (we need to set this up again as websocket connections are established per-UserSlot).
	const auto NotificationHandler = FOnContentRefreshNotificationCode::CreateLambda([this](const FContentRefreshNotificationMessage& ContentRefreshNotificationMessage)
	{
		// Our legacy solution here is that we delay grabbing the content so as to not make every single logged in client bombard the content service with
		// requests at the same time. We delay by a random amount in seconds as defined by the refresh message.
		const int32 DelayCount = FMath::RandRange(0, ContentRefreshNotificationMessage.Delay);

		// Configure an operation to run refresh the given content manifest some time in the future.
		FTimerHandle H;
		GetWorld()->GetTimerManager().SetTimer(H, FTimerDelegate().CreateLambda([this, ContentRefreshNotificationMessage]
		{
			const auto DelayedFetchAllOpHandler = FBeamOperationEventHandlerCode::CreateLambda([](FBeamOperationEvent OpEvent)
			{
				if (OpEvent.EventType == OET_ERROR)
				{
					// TODO: How should we handle when S3 explodes for some reason?
				}
			});

			// TODO: Only fetch the updated content items (scopes)
			const FBeamOperationHandle DelayedFetchAllOp = GEngine->GetEngineSubsystem<UBeamRequestTracker>()->CPP_BeginOperation({}, GetName(), DelayedFetchAllOpHandler);
			FetchContentManifest(ContentRefreshNotificationMessage.Manifest.Id, true, false, DelayedFetchAllOp);
			UE_LOG(LogBeamContent, Display, TEXT("Delay for ContentRefresh is over. Fetching the updated content manifest."));
		}), DelayCount, false, DelayCount);

		UE_LOG(LogBeamContent, Display, TEXT("Received ContentRefresh notification. Fetching content in %d seconds."), DelayCount);
	});
	GEngine->GetEngineSubsystem<UBeamContentNotifications>()->CPP_SubscribeToContentRefresh(UserSlot, Runtime->DefaultNotificationChannel, NotificationHandler, this);
}

void UBeamContentSubsystem::DownloadContentObjects(const FBeamContentManifestId ManifestId, const TArray<FBeamRemoteContentManifestEntry> Rows, const TMap<FBeamContentId, FString> Checksums,
                                                   const bool bIgnoreFilterMap, FBeamOperationHandle Op)
{
	// If there is no rows to download we complete the operation.
	if (Rows.Num() == 0)
	{
		this->Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
		return;
	}

	// We build a filter map (if requested), from the UBeamRuntimeSettings::IndividualContentDownloadFilter map.
	// This mostly runs only during the automatic content refreshes due to content notifications AND the initial content fetch if UBeamRuntimeSettings::bDownloadIndividualContentOnStart is set.
	// Users calling FetchContentManifestOperation manually, can opt-into using this filter or not.
	auto StringFilterMap = TMap<FString, FOptionalArrayOfBeamContentId>{};
	if (!bIgnoreFilterMap)
	{
		const auto FilterMap = GetDefault<UBeamRuntimeSettings>()->IndividualContentDownloadFilter;
		for (const auto& Kvp : FilterMap)
		{
			const auto TypeString = Kvp.Key.GetDefaultObject()->BuildContentTypeString();
			StringFilterMap.Add(TypeString, Kvp.Value);
		}
	}

	// Let's look for the list of content that needs fetching...
	TArray<FBeamRequestContext> IndividualDownloadRequests;
	for (const auto& ContentEntry : Rows)
	{
		if (ContentEntry.Type == EBeamContentType::BEAM_content)
		{
			// We verify if the optional is not set OR empty
			const auto ContentTypeId = ContentEntry.ContentId.GetTypeId();
			const auto FilteredContents = StringFilterMap.Find(ContentTypeId);

			// We should only try to download if the user did...
			const auto bShouldDownload = !FilteredContents || // Not enter a specific list of contents of this type to download
				!FilteredContents->IsSet || // Not enter a specific list of contents of this type to download				
				FilteredContents->Val.Contains(ContentEntry.ContentId); // OR, this content we are checking is on the list of things to download.
			// In other words, if the user wants to opt-out of downloading a particular content type, they can add an entry to the filter dictionary and leave its array as empty.			

			if (bShouldDownload)
			{
				// We only download changed content from the given manifest
				const auto Checksum = Checksums.Find({ContentEntry.ContentId});
				const auto bNotDownloaded = !Checksum;
				const auto bOlderVersionCached = Checksum && !ContentEntry.Version.Equals(*Checksum);
				if (bNotDownloaded || bOlderVersionCached)
				{
					auto Req = NewObject<UGenericBeamRequest>();
					Req->RequestTypeName = TEXT("BeamIndividualContentDownload");
					Req->Body = TEXT("");
					Req->Verb = TEXT("GET");
					Req->URL = ContentEntry.Uri;
					Req->CustomHeaders.Add(UBeamBackend::HEADER_ACCEPT, UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);

					// For each download that we'll make, register a lambda that:
					//  - Tries to save the downloaded file to the local '.beamable' folder.
					//  - Checks to see if it was the last download and, if so, invoke the appropriate on success/error callback.
					const auto IndividualContentHandler = FOnGenericBeamRequestFullResponse::CreateLambda([this, Op, ManifestId, ContentEntry](FGenericBeamRequestFullResponse Resp)
					{
						if (Resp.State == RS_Success)
						{
							auto ResponseJson = Resp.SuccessData->ResponseBody;


							// We create the object from the downloaded JSON and store it in the created cache.
							const auto Id = ContentEntry.ContentId;
							const auto Tags = ContentEntry.Tags;
							const auto ContentTypeId = Id.GetTypeId();

							// Fix-up since Unreal's JSON serializer expects true/false/null values to be upper case... Its not the correct spec, but... it is what it is... 
							ResponseJson.ReplaceInline(TEXT("\":true"), TEXT("\":True"));
							ResponseJson.ReplaceInline(TEXT("\":false"), TEXT("\":False"));
							ResponseJson.ReplaceInline(TEXT("\":null"), TEXT("\":Null"));

							// Create the ContentObject instance of the appropriate type.
							UBeamContentObject* ContentObject;
							UBeamContentObject::NewFromTypeId(ContentTypeStringToContentClass, ContentTypeId, ContentObject);

							// We should never reach here without a ContentObject instance.
							ensureAlwaysMsgf(ContentObject, TEXT("ContentObject was not created successfully. ManifestId=%s, ContentId=%s"), *ManifestId.AsString, *Id.AsString);
							UE_LOG(LogBeamContent, Verbose, TEXT("Downloaded content and preparing to parse its Json. CONTENT_ID=%s, JSON=%s, SUPPORT_LEVEL=%s"),
							       *Id.AsString, *ResponseJson, *StaticEnum<EBeamContentObjectSupportLevel>()->GetValueAsString(ContentObject->SupportLevel))

							// Deserialize the content object into the instance
							ContentObject->FromBasicJson(ResponseJson);
							ContentObject->Tags = Tags;


							// Cache the content object data in memory and update the hashes so that subsequent calls can figure out whether or not we need to redownload.
							const auto LiveContentCache = LiveContent.FindChecked(ManifestId);
							const auto PropertyHash = ContentObject->CreatePropertiesHash();
							LiveContentCache->Cache.Add(Id, ContentObject);
							LiveContentCache->Hashes.Add(Id, ContentObject->Version);

							UE_LOG(LogBeamContent, Verbose, TEXT("Downloaded and parsed content. CONTENT_ID=%s, HASH=%s, CONTENT_MANIFEST_ID=%s"), *Id.AsString,
							       *LiveContentCache->Hashes.FindChecked(Id),
							       *ManifestId.AsString)

							Runtime->RequestTrackerSystem->TriggerOperationEvent(Op, OET_SUCCESS, FName(TEXT("DOWNLOADED_INDIVIDUAL_CONTENT_SUCCESS")), ContentEntry.ContentId.AsString,
							                                                     Resp.Context.RequestId);
						}

						if (Resp.State == RS_Error)
						{
							Runtime->RequestTrackerSystem->TriggerOperationEvent(Op, OET_SUCCESS, FName(TEXT("DOWNLOADED_INDIVIDUAL_CONTENT_FAILED")), ContentEntry.ContentId.AsString,
							                                                     Resp.Context.RequestId);
						}
					});

					if (bNotDownloaded) UE_LOG(LogBeamContent, Verbose, TEXT("Content Id %s not in memory. Preparing to fetch its JSON blob."), *ContentEntry.ContentId.AsString);
					if (bOlderVersionCached) UE_LOG(LogBeamContent, Verbose, TEXT("Detected Changes in Content Id %s. Preparing to fetch its JSON blob."), *ContentEntry.ContentId.AsString);

					// Make the request
					const auto ReqId = GenericApi->CPP_ExecuteNonBeamRequest(Req, IndividualContentHandler, Op, this);
					IndividualDownloadRequests.Add(ReqId);
				}
			}
		}
	}

	if (IndividualDownloadRequests.Num() > 0)
	{
		const auto WaitIndividualDownloadsHandler = FOnWaitCompleteCode::CreateLambda([this, Op,ManifestId](FBeamWaitCompleteEvent Evt)
		{
			if (this->Runtime)
			{
				if (this->Runtime->RequestTrackerSystem->IsWaitSuccessful(Evt))
				{
					auto CoreSettings = GetMutableDefault<UBeamCoreSettings>();

					const FString CachedContentPath = FPaths::ProjectSavedDir() + CoreSettings->CachedContentFolderName + "/" + CoreSettings->GlobalCachedContentFileName;

					UBeamContentCache* SavedContent = LiveContent[ManifestId];

					TArray<uint8> SerializedData;
					FBeamMemoryWriter Writer(SerializedData, true);

					SavedContent->SerializeToBinary(Writer, ContentTypeStringToContentClass, ContentClassToContentTypeString);

					if (FFileHelper::SaveArrayToFile(SerializedData, *CachedContentPath))
					{
						UE_LOG(LogBeamContent, Log, TEXT("Cached new content."));
					}
					else
					{
						UE_LOG(LogBeamContent, Error, TEXT("Error while caching new content."));
					}

					this->Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
					return;
				}
				TArray<FString> Errs;
				if (this->Runtime->RequestTrackerSystem->IsWaitFailed(Evt, Errs))
				{
					this->Runtime->RequestTrackerSystem->TriggerOperationError(Op, FString::Join(Errs, TEXT("\n")));
					return;
				}
			}
		});
		Runtime->RequestTrackerSystem->CPP_WaitAll(IndividualDownloadRequests, {}, {}, WaitIndividualDownloadsHandler);
	}
	else
	{
		this->Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, {});
	}
}

bool UBeamContentSubsystem::AreContentsOfType(TSubclassOf<UBeamContentObject> AllowedType, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds)
{
	return ValidateContentsType({AllowedType}, Contents, InvalidContentIds);
}

bool UBeamContentSubsystem::AreContentsOfTypeHierarchy(TSubclassOf<UBeamContentObject> AllowedType, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds)
{
	return ValidateContentsTypeHierarchy({AllowedType}, Contents, InvalidContentIds);
}

bool UBeamContentSubsystem::ValidateContentsType(TArray<TSubclassOf<UBeamContentObject>> AllowedTypes, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds)
{
	TArray<FString> TypeStrings;
	for (TSubclassOf<UBeamContentObject> AllowedType : AllowedTypes)
	{
		const auto TypeString = ContentClassToContentTypeString[*AllowedType];
		TypeStrings.Add(TypeString);
	}

	for (FBeamContentId Content : Contents)
	{
		auto bIsAllowed = false;
		for (FString TypeString : TypeStrings)
			bIsAllowed |= Content.GetTypeId().Equals(TypeString);

		if (!bIsAllowed)
			InvalidContentIds.Add(Content);
	}

	return InvalidContentIds.IsEmpty();
}

bool UBeamContentSubsystem::ValidateContentsTypeHierarchy(TArray<TSubclassOf<UBeamContentObject>> AllowedTypes, TArray<FBeamContentId> Contents, TArray<FBeamContentId>& InvalidContentIds)
{
	TArray<FString> TypeStrings;
	for (TSubclassOf<UBeamContentObject> AllowedType : AllowedTypes)
	{
		const auto TypeString = ContentClassToContentTypeString[*AllowedType];
		TypeStrings.Add(TypeString);
	}

	for (FBeamContentId Content : Contents)
	{
		auto bIsAllowed = false;
		for (FString TypeString : TypeStrings)
			bIsAllowed |= Content.GetTypeId().StartsWith(TypeString);

		if (!bIsAllowed)
			InvalidContentIds.Add(Content);
	}

	return InvalidContentIds.IsEmpty();
}

bool UBeamContentSubsystem::TryGetContent(FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	return TryGetContentFromManifest(FBeamContentManifestId{"global"}, ContentId, OutContent);
}

bool UBeamContentSubsystem::TryGetContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	if (LiveContent.Contains(ManifestId))
	{
		const auto LiveManifest = LiveContent.FindRef(ManifestId);
		if (LiveManifest->Cache.Contains(ContentId))
		{
			OutContent = LiveManifest->Cache.FindRef(ContentId);
			return true;
		}

		const auto CookedManifest = BakedContent.FindRef(ManifestId);
		if (!CookedManifest)
		{
			UE_LOG(LogBeamContent, Warning, TEXT("No content with Id=%s was downloaded yet. Since the Manifest with Id=%s wasn't Baked, we can't provide this content."), *ContentId.AsString,
			       *ManifestId.AsString)
			return false;
		}

		if (CookedManifest->Cache.Contains(ContentId))
		{
			OutContent = CookedManifest->Cache.FindRef(ContentId);
			return true;
		}

		return false;
	}

	const auto CookedManifest = BakedContent.FindRef(ManifestId);
	if (!CookedManifest)
	{
		UE_LOG(LogBeamContent, Warning, TEXT("No content with Id=%s was downloaded yet. Since the Manifest with Id=%s wasn't Baked, we can't provide this content."), *ContentId.AsString,
		       *ManifestId.AsString)
		return false;
	}

	if (CookedManifest->Cache.Contains(ContentId))
	{
		OutContent = CookedManifest->Cache.FindRef(ContentId);
		return true;
	}

	return false;
}

bool UBeamContentSubsystem::IsLoadedContent(FBeamContentId ContentId)
{
	return IsLoadedContentFromManifest(FBeamContentManifestId{"global"}, ContentId);
}

bool UBeamContentSubsystem::IsLoadedContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId)
{
	if (LiveContent.Contains(ManifestId))
	{
		const auto LiveManifest = LiveContent.FindRef(ManifestId);
		if (LiveManifest->Cache.Contains(ContentId)) return true;

		const auto CookedManifest = BakedContent.FindRef(ManifestId);
		if (!CookedManifest) return false;
		if (CookedManifest->Cache.Contains(ContentId)) return true;

		return false;
	}

	const auto CookedManifest = BakedContent.FindRef(ManifestId);
	if (!CookedManifest) return false;
	if (CookedManifest->Cache.Contains(ContentId)) return true;

	return false;
}

bool UBeamContentSubsystem::TryGetBakedContent(FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	return TryGetBakedContentFromManifest(FBeamContentManifestId{"global"}, ContentId, OutContent);
}

bool UBeamContentSubsystem::TryGetBakedContentFromManifest(FBeamContentManifestId ManifestId, FBeamContentId ContentId, UBeamContentObject*& OutContent)
{
	checkf(BakedContent.Contains(ManifestId), TEXT("Manifest must exist in at least the baked content"))
	const auto CookedManifest = BakedContent.FindRef(ManifestId);
	if (CookedManifest->Cache.Contains(ContentId))
	{
		OutContent = CookedManifest->Cache.FindRef(ContentId);
		return true;
	}
	return false;
}

int UBeamContentSubsystem::GetIdsOfContentType(TSubclassOf<UBeamContentObject> Type, TArray<FBeamContentId>& Ids, bool bGetInherited)
{
	// TODO: We either need to cache the results (and invalidate when content updates) OR we need to change our RuntimeCache data structure into a search tree. 
	Ids.Reset();
	Ids.Reserve(256);
	for (const auto& Content : LiveContent)
	{
		for (const auto& Cache : Content.Value->Cache)
		{
			const auto Class = Cache.Value->GetClass();
			const auto bIsType = !bGetInherited && Class == Type.Get();
			const auto bInheritsFrom = bGetInherited && Class->IsChildOf(Type);

			if (bIsType || bInheritsFrom)Ids.AddUnique(Cache.Key);
		}
	}

	for (const auto& Content : BakedContent)
	{
		for (const auto& Cache : Content.Value->Cache)
		{
			const auto Class = Cache.Value->GetClass();
			const auto bIsType = !bGetInherited && Class == Type.Get();
			const auto bInheritsFrom = bGetInherited && Class->IsChildOf(Type);

			if (bIsType || bInheritsFrom)Ids.AddUnique(Cache.Key);
		}
	}
	return Ids.Num();
}

FBeamOperationHandle UBeamContentSubsystem::FetchContentManifestOperation(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, bool bIgnoreFilterMap,
                                                                          FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchContentManifest(ManifestId, bDownloadIndividualContent, bIgnoreFilterMap, Handle);
	return Handle;
}

FBeamOperationHandle UBeamContentSubsystem::CPP_FetchContentManifestOperation(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, bool bIgnoreFilterMap,
                                                                              FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchContentManifest(ManifestId, bDownloadIndividualContent, bIgnoreFilterMap, Handle);
	return Handle;
}

FBeamOperationHandle UBeamContentSubsystem::FetchIndividualContentBatchOperation(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownload,
                                                                                 FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchIndividualContent(ManifestId, ContentToDownload, Handle);
	return Handle;
}

FBeamOperationHandle UBeamContentSubsystem::CPP_FetchIndividualContentBatchOperation(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownloadFetch,
                                                                                     FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchIndividualContent(ManifestId, ContentToDownloadFetch, Handle);
	return Handle;
}

FBeamOperationHandle UBeamContentSubsystem::FetchIndividualContentOperation(FBeamContentManifestId ManifestId, FBeamContentId ContentToDownload, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchIndividualContent(ManifestId, {ContentToDownload}, Handle);
	return Handle;
}

FBeamOperationHandle UBeamContentSubsystem::CPP_FetchIndividualContentOperation(FBeamContentManifestId ManifestId, FBeamContentId ContentToDownload, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchIndividualContent(ManifestId, {ContentToDownload}, Handle);
	return Handle;
}

void UBeamContentSubsystem::FetchContentManifest(FBeamContentManifestId ManifestId, bool bDownloadIndividualContent, bool bIgnoreFilterMap, FBeamOperationHandle Op)
{
	const auto Request = UGetManifestPublicJsonRequest::Make(FOptionalBeamContentManifestId(ManifestId), {}, GetTransientPackage(), {});
	const auto Handler = FOnGetManifestPublicJsonFullResponse::CreateLambda([this, ManifestId, Op, bDownloadIndividualContent, bIgnoreFilterMap](FGetManifestPublicJsonFullResponse Resp)
	{
		if (Resp.State == RS_Retrying) return;

		if (Resp.State == RS_Success)
		{
			UBeamContentCache* Cache = NewObject<UBeamContentCache>();
			Cache->ManifestId = ManifestId;
			Cache->LatestRemoteManifest = TArray(Resp.SuccessData->Entries);

			const auto NumEntries = Cache->LatestRemoteManifest.Num();
			Cache->Cache.Reserve(NumEntries);
			Cache->Hashes.Reserve(NumEntries);

			TMap<FBeamContentId, FString> CurrentLocalHashes = {};
			if (LiveContent.Contains(ManifestId))
			{
				CurrentLocalHashes = LiveContent[ManifestId]->Hashes;
				LiveContent[ManifestId]->LatestRemoteManifest = Cache->LatestRemoteManifest;
			}
			else
			{
				LiveContent.Add(ManifestId, Cache);
			}

			if (bDownloadIndividualContent)
			{
				if (LiveContent.Contains(ManifestId))
				{
					const UBeamContentCache* ContentCache = LiveContent.FindChecked(ManifestId);

					const auto DownloadOpHandler = FBeamOperationEventHandlerCode::CreateLambda([this, ManifestId, Op](FBeamOperationEvent Evt)
					{
						// If all content was downloaded correctly.
						if (Evt.EventType == OET_SUCCESS && Evt.EventId == NAME_None)
						{
							ContentManifestsUpdated.Broadcast({ManifestId});
							GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
						}

						if (Evt.EventType == OET_ERROR && Evt.EventId == NAME_None)
						{
							GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, {});
						}
					});
					const auto DownloadOp = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetName(), DownloadOpHandler);
					DownloadContentObjects(ManifestId, ContentCache->LatestRemoteManifest, CurrentLocalHashes, bIgnoreFilterMap, DownloadOp);
				}
				else
				{
					// TODO: When we go into the Session service implementation and figure out online/offline modes and recovery, we need to revisit this.
					UE_LOG(LogBeamContent, Error, TEXT("Failed to download data on account of missing the live content manifest. This should only be seen when not connected to the internet."));
				}
			}
			else
			{
				ContentManifestsUpdated.Broadcast({ManifestId});
				GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationSuccess(Op, {});
			}
			return;
		}

		if (Resp.State == RS_Error)
		{
			GEngine->GetEngineSubsystem<UBeamRequestTracker>()->TriggerOperationError(Op, {});
		}
	});

	FBeamRequestContext Ctx;
	ContentApi->CPP_GetManifestPublicJson(Request, Handler, Ctx, Op, this);
}

void UBeamContentSubsystem::FetchIndividualContent(FBeamContentManifestId ManifestId, TArray<FBeamContentId> ContentToDownloadFetch, FBeamOperationHandle Op)
{
	ensureAlwaysMsgf(LiveContent.Contains(ManifestId),
	                 TEXT("Content Manifest %s was never fetched. Please ensure that the FetchContentManifest operation is called at least once for all of your manifests."), *ManifestId.AsString);

	const auto Cache = LiveContent.FindRef(ManifestId);

	TArray<FBeamRemoteContentManifestEntry> EntriesToDownload;
	for (auto ToDownloadFetch : ContentToDownloadFetch)
	{
		const auto Row = Cache->LatestRemoteManifest.FindByPredicate([&ToDownloadFetch](const FBeamRemoteContentManifestEntry& Entry) { return Entry.ContentId == ToDownloadFetch; });
		ensureAlwaysMsgf(Row, TEXT("Content Manifest %s does not contain a content with Id %s. Please ensure that this Id is of this manifest."), *ManifestId.AsString, *ToDownloadFetch.AsString);
		if (Row != nullptr)
		{
			// If this row is in the manifest, we'll see if we have it loaded already (or if the loaded version is not the same as the one in the manifest currently loaded.
			if (const FBeamContentId RowId{Row->ContentId}; IsLoadedContent(RowId))
			{
				UBeamContentObject* RowObj;
				if (TryGetContent(RowId, RowObj); RowObj->Version != Row->Version)
				{
					EntriesToDownload.Add(*Row);
				}
			}
			else
			{
				EntriesToDownload.Add(*Row);
			}
		}
	}

	DownloadContentObjects(ManifestId, EntriesToDownload, Cache->Hashes, true, Op);
}

bool UBeamContentSubsystem::EnforceLinks(FBeamContentManifestId ManifestId, TArray<FBeamRemoteContentManifestEntry> ManifestRows, TArray<FBeamContentId>& OutLinksToFetch)
{
	// For each of the downloaded content from the manifest, check if any of them have ContentLinks in them.
	for (const FBeamRemoteContentManifestEntry& ManifestRow : ManifestRows)
	{
		UBeamContentObject* Obj;
		if (TryGetContentOfTypeFromManifest(ManifestId, FBeamContentId{ManifestRow.ContentId}, Obj))
		{
			const auto ObjContentType = Obj->GetClass();

			if (const auto PathsToLinksPtr = PathsToContentLinks.Find(ObjContentType))
			{
				const auto PathsToLinks = *PathsToLinksPtr;

				// If we have no links here, we just log and skip.
				if (!PathsToLinks.Num()) UE_LOG(LogBeamContent, Verbose, TEXT("ContentObject of this type has no Content Links in it for us to pre-fetch. TYPE=%s"), *ObjContentType->GetName());

				// For each link we do have inside this ContentObject types... we extract the content id in it. 
				for (TArray<const FProperty*> PathToLink : PathsToLinks)
				{
					// Build the path to the content link from the recursive property root.
					ChaseContentLinkProperty(Obj, PathToLink, OutLinksToFetch);
				}
			}

			// Handle recursive properties...
			if (const auto PathsToRecursivePropsPtr = PathsToRecursiveProperties.Find(ObjContentType))
			{
				const auto PathsToRecursiveProps = *PathsToRecursivePropsPtr;
				const auto RecursivePropTypes = RecursivePropertyTypes.FindChecked(ObjContentType);

				if (!RecursivePropTypes.Num()) UE_LOG(LogBeamContent, Verbose, TEXT("ContentObject of this type has no Recursive Fields for us to look for Content Links in. TYPE=%s"),
				                                      *ObjContentType->GetName());

				// For each recursive root and its type...
				for (int i = 0; i < RecursivePropTypes.Num(); ++i)
				{
					const auto PathToRecursiveRoot = PathsToRecursiveProps[i];
					UClass* RecursiveRootType = RecursivePropTypes[i];

					const auto PathToRecursiveSelves = PathsToRecursiveSelves.Find(RecursiveRootType);

					// Get all the recursive root objects
					TArray<UObject*> EveryRecursiveRoot;
					ChaseRecursiveRoots(RecursiveRootType, *PathToRecursiveSelves, PathToRecursiveRoot, Obj, EveryRecursiveRoot);

					// For each recursive root object's ContentLink properties, grab its value.
					if (const auto PathsToLinksFromRecursiveRootPtr = PathsToContentLinks.Find(RecursiveRootType))
					{
						for (UObject* RecursiveInstance : EveryRecursiveRoot)
						{
							const auto PathToLinkFromRecursiveRoot = (*PathsToLinksFromRecursiveRootPtr);
							for (TArray<const FProperty*> PathToLinkFromRoot : PathToLinkFromRecursiveRoot)
							{
								ChaseContentLinkProperty(RecursiveInstance, PathToLinkFromRoot, OutLinksToFetch);
							}
						}
					}
				}
			}
		}

		for (FBeamContentId LinksToFetch : OutLinksToFetch)
		{
			UE_LOG(LogBeamContent, Verbose, TEXT("Found Content Link in Downloaded Content. TYPE=%s, LINK=%s"), *Obj->GetClass()->GetName(), *LinksToFetch.AsString);
		}
	}

	return OutLinksToFetch.Num() > 0;
}
