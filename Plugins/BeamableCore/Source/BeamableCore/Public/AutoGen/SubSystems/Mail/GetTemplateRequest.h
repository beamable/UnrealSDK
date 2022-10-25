
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"



#include "AutoGen/MailTemplate.h"

#include "GetTemplateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTemplateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Template Name", Category="Beam")
	FString TemplateName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	int64 GamerTag;

	// Body Params
	

	// Beam Base Request Declaration
	UGetTemplateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Mail", DisplayName="Beam - Make GetTemplate",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetTemplateRequest* Make(FString _TemplateName, int64 _GamerTag, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTemplateSuccess, FBeamRequestContext, Context, UGetTemplateRequest*, Request, UMailTemplate*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTemplateError, FBeamRequestContext, Context, UGetTemplateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTemplateComplete, FBeamRequestContext, Context, UGetTemplateRequest*, Request);

using FGetTemplateFullResponse = FBeamFullResponse<UGetTemplateRequest*, UMailTemplate*>;
DECLARE_DELEGATE_OneParam(FOnGetTemplateFullResponse, FGetTemplateFullResponse);
