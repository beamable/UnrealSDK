
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/GetManifestDiffsResponse.h"

#include "GetManifestDiffsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetManifestDiffsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest Id", Category="Beam")
	FBeamContentManifestId ManifestId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From Uid", Category="Beam")
	FOptionalString FromUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To Uid", Category="Beam")
	FOptionalString ToUid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset", Category="Beam")
	FOptionalInt32 Offset = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From Date", Category="Beam")
	FOptionalInt64 FromDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To Date", Category="Beam")
	FOptionalInt64 ToDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetManifestDiffsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestDiffs",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_FromUid,_ToUid,_Offset,_FromDate,_ToDate,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetManifestDiffsRequest* Make(FBeamContentManifestId _ManifestId, FOptionalString _FromUid, FOptionalString _ToUid, FOptionalInt32 _Offset, FOptionalInt64 _FromDate, FOptionalInt64 _ToDate, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestDiffsSuccess, FBeamRequestContext, Context, UGetManifestDiffsRequest*, Request, UGetManifestDiffsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetManifestDiffsError, FBeamRequestContext, Context, UGetManifestDiffsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetManifestDiffsComplete, FBeamRequestContext, Context, UGetManifestDiffsRequest*, Request);

using FGetManifestDiffsFullResponse = FBeamFullResponse<UGetManifestDiffsRequest*, UGetManifestDiffsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetManifestDiffsFullResponse, FGetManifestDiffsFullResponse);
