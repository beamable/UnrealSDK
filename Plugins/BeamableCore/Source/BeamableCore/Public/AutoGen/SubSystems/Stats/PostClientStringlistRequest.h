
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/StatUpdateRequestStringListFormat.h"
#include "AutoGen/EmptyResponse.h"

#include "PostClientStringlistRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostClientStringlistRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UStatUpdateRequestStringListFormat* Body;

	// Beam Base Request Declaration
	UPostClientStringlistRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Set,Outer"))
	static UPostClientStringlistRequest* MakePostClientStringlistRequest(FString _ObjectId, FOptionalArrayOfStatStringListEntry _Set, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientStringlistSuccess, FBeamRequestContext, Context, UPostClientStringlistRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientStringlistError, FBeamRequestContext, Context, UPostClientStringlistRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostClientStringlistComplete, FBeamRequestContext, Context, UPostClientStringlistRequest*, Request);

using FPostClientStringlistFullResponse = FBeamFullResponse<UPostClientStringlistRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostClientStringlistFullResponse, FPostClientStringlistFullResponse);
