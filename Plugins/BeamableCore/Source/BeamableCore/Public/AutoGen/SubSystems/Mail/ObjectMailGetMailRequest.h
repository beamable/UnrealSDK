
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/MailQueryResponse.h"

#include "ObjectMailGetMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailGetMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectMailGetMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UObjectMailGetMailRequest* MakeObjectMailGetMailRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailGetMailSuccess, FBeamRequestContext, Context, UObjectMailGetMailRequest*, Request, UMailQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailGetMailError, FBeamRequestContext, Context, UObjectMailGetMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailGetMailComplete, FBeamRequestContext, Context, UObjectMailGetMailRequest*, Request);

using FObjectMailGetMailFullResponse = FBeamFullResponse<UObjectMailGetMailRequest*, UMailQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailGetMailFullResponse, FObjectMailGetMailFullResponse);
